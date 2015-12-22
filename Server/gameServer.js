module.exports = function GameServer(serverPort) 
{
	var port = serverPort;
	var numberOfPlayers = 0;

	this.addPlayer = function()
	{
		++numberOfPlayers;
	};

	this.getPort = function()
	{
		return port;
	}
}