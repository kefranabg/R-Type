//
// Server.cpp for Server.cpp in /home/abgral_f/dev/R-Type/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Nov 11 11:21:48 2014 abgral_f
// Last update Sat Dec 20 13:47:03 2014 abgral_f
//

#include "Server.hh"
#include "Game.hh"

Server::Server()
{
#ifdef                  _WIN32
	socket = new WinSocket();
#else
	socket = new UnixSocket();
#endif
	if (socket->socketInit(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == -1
		|| socket->socketBind() == -1)
		throw std::runtime_error(INIT_ERROR);
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

Server::~Server() {
	delete (socket);
}

static int		stopServer(int value)
{
	static int		stopValue = 0;

	if (value != 0)
		stopValue = value;
	return (stopValue);
}

#ifdef			_WIN32
DWORD WINAPI		readInput(LPVOID param) {
	std::string		line;
	bool			stop = false;

	static_cast<void>(param);
	while (stop == false) {
		if (!std::getline(std::cin, line, '\n'))
			std::cin.clear();
		else if (line == QUIT_CMD) {
			stop = true;
			stopServer(1);
		}
	}
	return (0);
}
#endif

void			Server::checkInput()
{
	std::string		input;

	if (!std::getline(std::cin, input, '\n'))
		std::cin.clear();
	else if (input == QUIT_CMD)
		stopServer(1);
}

packetRecv		*Server::getMsg()
{
	int			readed;
	packetRecv		*packet = new packetRecv();
	socklen_t		length = sizeof(packet->infos);

	packet->data.resize(SIZE_MAX_PACKET + 1);
	if ((readed = recvfrom(socket->getSocket(), packet->data.data(), SIZE_MAX_PACKET, 0,
		(struct sockaddr *)&packet->infos, &length)) == -1)
		throw std::runtime_error(READ_SOCKET_ERROR);
	if (static_cast<unsigned int>(readed) < sizeof(int))
		throw std::runtime_error(WRONG_PACKET);
	packet->data.resize(readed);
	return (packet);
}

void			Server::initSelect()
{
	select.fdsZero("rwe");
	tv.tv_sec = 0;
	tv.tv_usec = TV_USEC;
#ifndef			WIN32
	select.fdsSet("r", 0);
#endif
	select.fdsSet("r", socket->getSocket());
	select.doSelect(&tv);
}

ClientOpcodes			Server::getOpcode(const std::vector<char> &data) const
{
	ClientOpcodes		opcode;

	memcpy(&opcode, data.data(), sizeof(opcode));
	return (opcode);
}

static protocolFunctions protocols[NB_OPCODES] =
{
	{ CONNECT_REQUEST, &Server::connectRecv },
	{ CREATE_POOL_REQUEST, &Server::createPoolRecv },
	{ CHOOSEN_MAP, &Server::choosenMapRecv },
	{ LIST_PLAYER_REQUEST, &Server::listPlayerRecv },
	{ LIST_POOL_REQUEST, &Server::listPoolRecv },
	{ JOIN_POOL_REQUEST, &Server::joinPoolRecv },
	{ STATUS, &Server::statusRecv },
	{ QUIT_POOL, &Server::quitPoolRecv },
	{ PLAYER_ACTION, &Server::playerActionRecv },
	{ DIE, &Server::playerDieRecv },
	{ READY_TO_GAME, &Server::readyToGameRecv },
	{ PLAYER_FINISH, &Server::playerFinishRecv },
	{ CHOOSEN_NAME_REQUEST, &Server::chooseNameRecv },
	{ LIST_MAP_REQUEST, &Server::listMapRecv },
	{ PLAYER_DISCONNECT, &Server::disconnectRecv }
};

void			Server::processPacketReception()
{
	packetRecv			*packet = getMsg();
	ClientOpcodes			opcode = getOpcode(packet->data);

	packet->data.erase(packet->data.begin(), packet->data.begin() + sizeof(ClientOpcodes));
	for (int i = 0; i < NB_OPCODES; i++)
	if (protocols[i].opcode == opcode)
		(this->*(protocols[i]).protocolFunction)(packet);
	delete (packet);
}

void			Server::start()
{
#ifdef			_WIN32
	WinThread		input;

	if (input.threadCreate(&readInput, NULL) == -1)
		return;
#endif
	while (stopServer(0) == 0)
	{
#ifndef				WIN32
		if (select.isFdSet('r', 0) == true)
			checkInput();
#endif
		if (select.isFdSet('r', socket->getSocket()) == true)
		{
			try {
				processPacketReception();
			}
			catch (std::runtime_error e) {
				std::cerr << e.what() << std::endl;
			}
		}
		initSelect();
	}
	disconnectClient(0, true);
	socket->socketQuit();
}

const ServerSend						&Server::getDoPacket() const
{
	return (this->doPacket);
}

void                            Server::sendPacket(const std::vector<char> *packet,
struct sockaddr_in *addr) const
{
	int                           ret;

	try {
		if ((ret = sendto(socket->getSocket(), packet->data(), packet->size(), 0,
			(struct sockaddr *)addr, sizeof(*addr))) == -1)
		{
			delete(packet);
			throw std::runtime_error(WRITE_SOCKET_ERROR);
		}
		delete(packet);
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<std::string>			*Server::getFilesList(std::string const &pathName)
{
	std::vector<std::string> *ret = new std::vector<std::string>;
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(pathName.c_str())) != NULL)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_type == DT_REG)
				ret->push_back(std::string(entry->d_name));
		}
		closedir(dir);
	}
	else
		throw std::runtime_error("[ERROR] : Could not open directory \"" + pathName);
	return ret;
}

std::string const			Server::isMapValid(std::vector<std::vector<char>> const *map)
{
	if (map->size() != MAP_HEIGHT)
	{
		std::ostringstream oss;

		oss << "[ERROR] : Map's height is incorrect. Good height is 14";
		return (oss.str());
	}
	for (unsigned int y = 0; y < map->size(); y++)
	{
		if (map->at(y).size() < MAP_LENGTH)
		{
			std::ostringstream oss;

			oss << "[ERROR] : Line " << y << " does not have a valid length.";
			return (oss.str());
		}
		for (unsigned int x = 0; x < map->at(y).size(); x++)
		{
		  if (map->at(y)[x] != '0' && map->at(y)[x] != '1')
			{
				std::ostringstream oss;
				std::cout << "|||" << map->at(y)[x] << "|" << std::endl;
				oss << "[ERROR] : Character " << x << " at line " << y << " is invalid";
				return (oss.str());
			}
		}
	}
	return (MAP_SUCCESS);
}

std::vector<std::vector<char>> *Server::getMapData(std::string const &mapName)
{
	std::ifstream ifs(mapName.c_str());
	char c;
	std::vector<std::vector<char>> *ret = new std::vector<std::vector<char>>;
	std::vector<char> tmp;
	unsigned int countSize = -1;

	if (ifs.is_open() == false)
	{
		std::ostringstream oss;
		oss << "[ERROR] : \"" << mapName << "\" does not exist";
		throw std::runtime_error(oss.str());
	}
	if (ifs.peek() == std::ifstream::traits_type::eof())
		throw std::runtime_error("[ERROR] : file is empty");
	while (ifs.get(c) && ++countSize < MAX_MAP_SIZE)
	if (c == '\n')
	{
		ret->push_back(tmp);
		tmp.clear();
	}
	else if (c != '\r')
	  tmp.push_back(c);
	ret->push_back(tmp);
	std::string sMapValid = isMapValid(ret);
	if (sMapValid != MAP_SUCCESS)
		throw std::runtime_error(sMapValid);
	return ret;
}

int					Server::assignRoomId() const
{
	bool			check;

	for (unsigned int tmp_id = 0; tmp_id < MAX_ROOM; tmp_id++)
	{
		check = true;
		for (unsigned int i = 0; i < threadPools.size(); i++)
		{
			if (tmp_id == threadPools[i]->getId())
				check = false;
		}
		if (check == true)
			return (tmp_id);
	}
	return (-1);
}

void				Server::disconnectClient(int id, bool allClients)
{
	if (allClients == true)
	{
		while (clients.size() > 0)
		{
			sendPacket(doPacket.disconnectSnd(), clients.back()->getAddr());
			clients.pop_back();
		}
		return;
	}
	for (unsigned int i = 0; i < clients.size(); i++)
		if (id == clients[i]->getId())
		{
			sendPacket(doPacket.disconnectSnd(), clients[i]->getAddr());
			clients.erase(clients.begin() + i);
			return;
		}
}

ClientInfo			*Server::getClientByAddr(struct sockaddr_in *addr) const
{
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		if (addr->sin_port == clients[i]->getAddr()->sin_port
			&& addr->sin_addr.s_addr == clients[i]->getAddr()->sin_addr.s_addr)
			return (clients[i]);
	}
	return (NULL);
}

void				Server::connectRecv(packetRecv *packet)
{
	bool		                  check;

	for (int tmp_id = 0; tmp_id != MAX_CLIENTS; tmp_id++)
	{
		check = true;
		for (std::vector<ClientInfo *>::iterator it = clients.begin();
			it != clients.end(); ++it)
		{
			if (tmp_id == (*it)->getId())
				check = false;
		}
		if (check == true)
		{
			clients.push_back(new ClientInfo(tmp_id, &packet->infos));
			sendPacket(doPacket.connectSnd(true, tmp_id), clients.back()->getAddr());
			std::cout << "New client connected. id => " << tmp_id << std::endl;
			return;
		}
	}
	sendPacket(doPacket.connectSnd(false, -1), &packet->infos);
	std::cout << "Server full can't connect new client" << std::endl;
}

void				Server::chooseNameRecv(packetRecv *packet)
{
	ClientInfo			*client;
	NameInfos			s_data;
	std::string			name;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	if (packet->data.size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, packet->data.data(), sizeof(s_data));
	name = s_data.name;
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getName() == name)
		{
			sendPacket(doPacket.chooseNameSnd(false), &packet->infos);
			std::cout << "Client with id " << client->getId() << " wanted to change his name to "
				<< name << " but it already exist" << std::endl;
			return;
		}
	}
	client->setName(name);
	sendPacket(doPacket.chooseNameSnd(true), &packet->infos);
	std::cout << "Client with id " << client->getId() << " is now known as " << client->getName() << std::endl;
}

void				Server::createPoolRecv(packetRecv *packet)
{
	ClientInfo                    *client;
	PoolNameInfos                 s_data;
	std::string                   name;
	int							id;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	if (packet->data.size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, packet->data.data(), sizeof(s_data));
	name = s_data.poolName;
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (threadPools[i]->getName() == name)
	{
		sendPacket(doPacket.createPoolSnd(false, ""), &packet->infos);
		std::cout << client->getName() << " want to create a pool : " << name << " but it already exist" << std::endl;
		return;
	}
	if ((id = assignRoomId()) == -1)
	{
		std::cout << "Server is full of threadPools" << std::endl;
		sendPacket(doPacket.createPoolSnd(false, ""), &packet->infos);
		return;
	}
	threadPools.push_back(new Game(this, name, client, id));
	sendPacket(doPacket.createPoolSnd(true, client->getName()), &packet->infos);
	client->setRoomId(id);
	std::cout << client->getName() << " created the pool : " << name << std::endl;
}

void				Server::choosenMapRecv(packetRecv *packet)
{
	ClientInfo                    *client;
	MapNameInfos	                s_data;
	std::string                   name;
	std::string						path;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	if (packet->data.size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, packet->data.data(), sizeof(s_data));
	name = s_data.mapName;

#ifdef WIN32
	path = "..\\..\\..\\maps\\";
#else
	path = "../maps/";
#endif
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (client->getRoomId() == static_cast<int>(threadPools[i]->getId()))
		threadPools[i]->setMap(getMapData(path + name));
}

void				Server::listPlayerRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId() && clients[i]->getId() != client->getId())
		sendPacket(doPacket.playerJoinPoolSnd(clients[i]->getName(), clients[i]->getId()), client->getAddr());
}

void				Server::listPoolRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (threadPools[i]->getIsGameFinish() == true)
		sendPacket(doPacket.listPoolSnd(threadPools[i]->getName()), &packet->infos);
}


void				Server::joinPoolRecv(packetRecv *packet)
{
	ClientInfo                    *client;
	PoolNameInfos			s_data;
	std::string			name;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	if (packet->data.size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, packet->data.data(), sizeof(s_data));
	name = s_data.poolName;
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (threadPools[i]->getName() == name && threadPools[i]->getIsGameFinish() == true)
	{
		if (threadPools[i]->getPlayersNb() < 4)
		{
			sendPacket(doPacket.joinPoolSnd(SUCCESS, client->getName()), &packet->infos);
			threadPools[i]->addPlayer(client);
			client->setRoomId(threadPools[i]->getId());
			for (unsigned int i = 0; i < clients.size(); i++)
			if (clients[i]->getRoomId() == client->getRoomId() && clients[i]->getId() != client->getId())
				sendPacket(doPacket.playerJoinPoolSnd(client->getName(), client->getId()), clients[i]->getAddr());
			std::cout << client->getName() << " has joined the pool" << std::endl;
			return;
		}
		sendPacket(doPacket.joinPoolSnd(GAME_FULL, ""), &packet->infos);
		std::cout << client->getName() << " wanted to join the pool : " << name << " but it is full" << std::endl;
		return;
	}
	sendPacket(doPacket.joinPoolSnd(GAME_DOESNT_EXIST, ""), &packet->infos);
	std::cout << client->getName() << " wanted to join the pool : " << name << " but it doesn't exist anymore" << std::endl;
}

void				Server::statusRecv(packetRecv *packet)
{
	ClientInfo                    *client;
	PlayerStatusInfos		s_data;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	if (packet->data.size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, packet->data.data(), sizeof(s_data));
	client->setIsReady(s_data.isReady);
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId())
		sendPacket(doPacket.playerStatusSnd(s_data.isReady, client->getId(), client->getName()), clients[i]->getAddr());
	std::cout << client->getName() << " has a new status : " << s_data.isReady << std::endl;
}

void				Server::quitPoolRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId() && clients[i]->getId() != client->getId())
		sendPacket(doPacket.playerQuitSnd(client->getId(), client->getName()), clients[i]->getAddr());
	for (unsigned int y = 0; y < threadPools.size(); y++)
	if (static_cast<int>(threadPools[y]->getId()) == client->getRoomId())
		threadPools[y]->delPlayer(client->getId());
	client->setIsReady(false);
	client->setRoomId(-1);
	std::cout << client->getName() << " left the pool" << std::endl;
}

void				Server::playerActionRecv(packetRecv *packet)
{
	ClientInfo                    *client;
	ActionInfos			s_data;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	if (packet->data.size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, packet->data.data(), sizeof(s_data));
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (client->getRoomId() == static_cast<int>(threadPools[i]->getId()))
		threadPools[i]->setPlayerNextAction(client->getId(), s_data.action);
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId() && clients[i]->getId() != client->getId())
		sendPacket(doPacket.playerActionSnd(client->getId(), s_data.action), clients[i]->getAddr());
	//std::cout << client->getName() << " action : " << s_data.action << std::endl;
}

void				Server::playerDieRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (client->getRoomId() == static_cast<int>(threadPools[i]->getId()))
		threadPools[i]->setPlayerIsAlive(client->getId(), false);
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId())
		sendPacket(doPacket.playerDieSnd(client->getId()), clients[i]->getAddr());
	std::cout << client->getName() << " died" << std::endl;
}

void				Server::readyToGameRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	client->setIsReadyToGame(true);
	std::cout << client->getName() << " is ready to game" << std::endl;
}

void				Server::playerFinishRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (client->getRoomId() == static_cast<int>(threadPools[i]->getId()))
		threadPools[i]->setIsGameFinish(true);
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId())
		sendPacket(doPacket.endGameSnd(true), clients[i]->getAddr());
	std::cout << client->getName() << " finish the lvl !" << std::endl;
}

void				Server::listMapRecv(packetRecv *packet)
{
	ClientInfo                    *client;
	std::string						path;
	std::vector<std::string>		*mapsNames;
	std::vector<std::vector<char>> *map;

	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);

#ifdef WIN32
	path = "..\\..\\..\\maps\\";
#else
	path = "../maps/";
#endif
	mapsNames = getFilesList(path);
	for (unsigned int i = 0; i < mapsNames->size(); i++)
	{
		try {
			map = getMapData(path + mapsNames->at(i));
			delete(map);
			sendPacket(doPacket.listMapSnd(mapsNames->at(i)), &packet->infos);
		}
		catch (std::runtime_error e) {
			std::cerr << e.what() << std::endl;
		}
	}

}

void				Server::disconnectRecv(packetRecv *packet)
{
	ClientInfo                    *client;

	std::cout << "deleted" << std::endl;
	if ((client = getClientByAddr(&packet->infos)) == NULL)
		throw std::runtime_error(UNKNOWN_CLIENT);
	for (unsigned int i = 0; i < threadPools.size(); i++)
	if (client->getRoomId() == static_cast<int>(threadPools[i]->getId()))
		threadPools[i]->delPlayer(client->getId());
	for (unsigned int i = 0; i < clients.size(); i++)
	if (clients[i]->getRoomId() == client->getRoomId() && clients[i]->getId() != client->getId())
		sendPacket(doPacket.playerQuitSnd(client->getId(), client->getName()), clients[i]->getAddr());
	for (unsigned int i = 0; i < clients.size(); i++)
	if (client->getId() == clients[i]->getId())
		clients.erase(clients.begin() + i);

}
