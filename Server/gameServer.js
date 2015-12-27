module.exports = function GameServer(serverIP, serverPort) 
{
	var port = serverPort;
	var ip = serverIP;
	var numberOfPlayers = 0;

	this.addPlayer = function()
	{
		++numberOfPlayers;
		console.log(numberOfPlayers);
	};

	this.getNumberOfPlayers = function()
	{
		return numberOfPlayers;
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