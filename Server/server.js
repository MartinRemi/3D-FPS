// constants
const MAX_NUMBER_OF_PLAYERS = 2;

const GAME_NAME = "Awesome FPS"
// dependencies
var net = require('net');
var http = require('http');
var GameServer = require('./gameServer');

// ---------------------------------------------------------------------------
var options = 
{
	"verbose" : false,
	"masterServerPort" : 1337,
	"slaveServerPort" : 4242,
}
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
			newGameServer = new GameServer("127.0.0.1", options.slaveServerPort)
			servers.push(newGameServer);
			console.log("\tServer created on port "+newGameServer.getPort());
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
		if(options.verbose) {
			console.log("\tAnwsered: " + message);
		}
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
			var portNum = parseInt(jsonData["port_number"]);
			console.log("\tNew server to register ("+socket.remoteAddress+":"+portNum+")");
			servers.push(new GameServer(socket.remoteAddress, portNum));
		}
		else if(jsonData["message_type"] === "UNSR")
		{
			
			var portToClose = parseInt(jsonData["port_number"]);
			for(var i = 0; i < servers.length; ++i)
			{
				if(servers[i].getIP() == socket.remoteAddress && servers[i].getPort() == portToClose)
				{
					delete servers.slice(i, 1);
					break;
				}
			}
			console.log("\tServer unregistered ("+socket.remoteAddress+":"+portToClose+")");
		}
	};

	socket.on('data', function(data) 
	{
		var txtData = data.toString();
		var packetData = txtData;
		if(options.verbose) {
			console.log('Data from: '+socket.remoteAddress + ":" + socket.remotePort);
			console.log("\tPayload: " + data);
		}
		try {
			handleData(packetData);
		}catch(err){
			if(txtData.slice(0,3) == "GET"){
				console.log("\tGET Request");
				body = {}
				for(var i = 0; i < servers.length; ++i)
				{
					body[i] = servers[i].toJSON();
				}
				body = JSON.stringify(body);
				header = "HTTP/1.1 200 OK\r\n"
				header += "Server: Awesome\r\n"
				header += "Content-Length: "+(body.length)+"\r\n"
				header += "Content-Type: application/json\r\n"
				header += "Connection: Closed\r\n"
				response = header+"\r\n"+body;
				socket.write(response);
			}else{
				console.log("\tException - bad message");
				console.log("\tMessage from "+socket.remoteAddress + ":" + socket.remotePort);
			}
		}
	});
});

var main = function()
{
	server.listen(options.masterServerPort, '127.0.0.1');
}

/** Read the command line parameters
* return code < 0 if the server shouldn't be launched for some reason */
var argProcessing = function()
{
	var args = process.argv.slice(2);
	if (args.indexOf("-h") >= 0 || args.indexOf("--help") >= 0) {
		console.log("Master server for "+GAME_NAME);
		console.log("USAGE: node server.js <options>");
		console.log("options:");
		console.log("\t -h, --help \t\t\tDisplay help and exit");
		return -1;
	}
	if (args.indexOf("-v") >= 0 || args.indexOf("--verbose") >= 0) {
		options.verbose = true;
	}
	return 0;
}

if(require.main === module)
{
	if(argProcessing() >= 0) {
		main();
		console.log("Master server Ready on port "+options.masterServerPort);
		console.log("---------------------------------");
	}
}