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
		var message = servers[serv].getIP() + " " + servers[serv].getPort();
		socket.write(message);
		console.log("\tAnsered: " + message);
	}

	var handleData = function(data)
	{
		var subs = data.substring(0, 4);
		if(subs === "CLRS") // CLient Request Server
		{
			console.log("\tUser request server");
			answerClient(matchmaking());
		}
		else if(subs === "NWSR") // NeW ServeR
		{
			console.log("\tNew server to register");
			servers.push(new GameServer(socket.remoteAddress, parseInt(data.substring(4))));
		}
		else if(subs === "UNSR")
		{
			console.log("\tServer unregistred");
		}
	};

	socket.on('data', function(data) 
	{
		var packetData = data.toString();
		console.log("received: " + data);
		handleData(packetData);
	});

	socket.on('end', function()
	{
		console.log('disconnected');
	});
});

server.listen(1337, '127.0.0.1');