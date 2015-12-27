var net = require('net');
var GameServer = require('./gameServer');

var gameServ = null;
var servers = [];

var server = net.createServer(function(socket) 
{
	var matchmaking = function()
	{
		if(gameServ == null) 
			{
				gameServ = new GameServer("127.0.0.1", 4242);
				console.log("\tServer created on port 4242");
			}
			gameServ.addPlayer();
	};

	var answerClient = function()
	{
		var message = socket.localAddress + " " + gameServ.getPort();
		socket.write(message);
		console.log("\tAnsered: " + message);
	}

	var handleData = function(data)
	{
		var subs = data.substring(0, 4);
		if(subs === "CLRS") // CLient Request Server
		{
			console.log("\tUser request server");
			matchmaking();
			answerClient();
		}
		else if(subs === "NWSR") // NeW ServeR
		{
			console.log("\tNew server to register");
			gameServ = new GameServer(socket.remoteAddress, parseInt(data.substring(4)));
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