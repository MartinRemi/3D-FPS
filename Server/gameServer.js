module.exports = function GameServer(serverIP, serverPort) 
{
	var port = serverPort;
	var ip = serverIP;
	var numberOfPlayers = 0;

	this.addPlayer = function()
	{
		++numberOfPlayers;
	};

	this.getPort = function()
	{
		return port;
	};

	this.getIP = function()
	{
		return ip;
	}
}