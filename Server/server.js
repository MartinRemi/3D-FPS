const MAX_NUMBER_OF_PLAYERS = 2;

var net = require('net');
var GameServer = require('./gameServer');

var servers = [];

var server = net.createServer(function(socket) 
{
	var matchmaking = function()
	{
		var matchingServer = -1;
		for(var i = 0; i < servers.length; ++i)
		{
			if(servers[i].getNumberOfPlayers() < MAX_NUMBER_OF_PLAYERS)
			{
				matchingServer = i;
				console.log("\tServer found");
				break;
			}
		}
		if(servers.length === 0 || matchingServer == -1) 
		{
			servers.push(new GameServer("127.0.0.1", 4242));
			console.log("\tServer created on port 4242");
			matchingServer = servers.length - 1;
		}
		servers[matchingServer].addPlayer(); // FIX
		return matchingServer;
	};

	var answerClient = function(serv)
	{
		// FIX
		var jsonMessage = {};
		jsonMessage["message_type"] = "SRAV"; // Server available
		jsonMessage["server_ip"] = servers[serv].getIP();
		jsonMessage["server_port"] = servers[serv].getPort();
		var message = JSON.stringify(jsonMessage);
		socket.write(message);
		console.log("\tAnsered: " + message);
	}

	var handleData = function(data)
	{
		var jsonData = JSON.parse(data);
		if(jsonData["message_type"] === "CLRS") // CLient Request Server
		{
			console.log("\tUser request server");
			answerClient(matchmaking());
		}
		else if(jsonData["message_type"] === "NWSR") // NeW ServeR
		{
			console.log("\tNew server to register");
			servers.push(new GameServer(socket.remoteAddress, parseInt(jsonData["port_number"])));
		}
		else if(jsonData["message_type"] === "UNSR")
		{
			console.log("\tServer unregistred");
			var portToClose = parseInt(jsonData["port_number"]);
			for(var i = 0; i < servers.length; ++i)
			{
				if(servers[i].getIP() == socket.remoteAddress && servers[i].getPort() == portToClose)
				{
					delete servers.slice(i, 1);
					break;
				}
			}
		}
	};

	socket.on('data', function(data) 
	{
		var packetData = data.toString();
		console.log("received: " + data);
		handleData(packetData);
	});
});

server.listen(1337, '127.0.0.1');