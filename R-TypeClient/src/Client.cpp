//
// Client.cpp for Client.cpp in /home/abgral_f/dev/R-Type/R-TypeClient
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Sun Nov 16 17:18:48 2014 abgral_f
// Last update Sun Nov 23 10:18:06 2014 abgral_f
//

#include		"Client.hh"
#include		"Game.hh"
#include		"Gui.hh"
#include		"Menus.h"

Client::Client()
{
	exit = false;
	menu = new Menus(this);
#ifdef                  _WIN32
  socket = new WinSocket();
#else
  socket = new UnixSocket();
#endif
  if (socket->socketInit(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == -1)
    throw std::runtime_error(SOCKET_INIT_ERROR);
  this->isConnected = false;
  this->id = -1;
  this->pool = NULL;
  this->gui = NULL;
  this->music = new Music();
}

Client::~Client()
{
  socket->socketQuit();
  delete (socket);
}

bool				Client::Connection(int port, const std::string &ip)
{
  std::vector<char>		*data;
  int					flag;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip.c_str());
#ifdef					WIN32
  flag = WIN_MSG_DONTWAIT;
#else
  flag = MSG_DONTWAIT;
#endif
  try {
    sendPacket(doPacket.connectSnd());
    for (int i = 0; i < CONNECTION_WAIT; i++)
      {
#ifdef			WIN32
		Sleep(1000);
#else
	sleep(1);
#endif
	try {
	  data = getMsg(flag);
	  if (data->size() == sizeof(int) + sizeof(ConnectInfos))
	    {
	      data->erase(data->begin(), data->begin() + sizeof(int));
	      connectRecv(data);
	    }
	  delete(data);
	  return true;
	}
	catch (std::runtime_error e) {
	  std::cout << "Connecting" << std::endl;
	}
      }
  }
  catch (std::runtime_error e) {
    std::cout << e.what() << std::endl;
    return false;
  }
  std::cerr << CONNECTION_ERROR << std::endl;
  return false;
}

Game				*Client::getGame() const
{
	return (this->pool);
}

void				Client::setExit(bool value)
{
	exit = value;
}

bool				Client::getIsConnected() const
{
  return (this->isConnected);
}

void				Client::initSelect()
{
  select.fdsZero("rwe");
  tv.tv_sec = 0;
  tv.tv_usec = TV_USEC;
  select.fdsSet("r", socket->getSocket());
  select.doSelect(&tv);
}

void				Client::start()
{
	int i = 0;

	this->music = new Music();
	this->launchGui = new std::thread(startGui, this);

	while (isConnected == false && exit == false)
	{
#ifdef			WIN32
		Sleep(TIMER_WAITING_ROOM);
#else
		usleep( TIMER_WAITING_ROOM * 1000);
#endif
	}
  while (isConnected == true && exit == false)
    {
      if (select.isFdSet('r', socket->getSocket()) == true)
        {
          try {
	    processPacketReception();
	  }
          catch (std::runtime_error e) {
	    std::cout << e.what() << std::endl;
          }
	  }
	  initSelect();
	  i++;
    }
}

void		startGui(Client *client)
{
	client->launchMenu();
}

void Client::launchMenu()
{
	this->menu->startNewMenu();
}

void Client::launchGameGui(sf::RenderWindow *window)
{
	this->gui = new Gui(this, window);

	this->gui->aff();
	delete this->gui;
}

const ClientSend	&Client::getDoPacket() const
{
	return (this->doPacket);
}

void				Client::sendPacket(const std::vector<char> *packet) const
{
  int				readed;

  try {
    if ((readed = sendto(socket->getSocket(), packet->data(), packet->size(), 0,
			 (struct sockaddr *)&addr, sizeof(addr))) == -1)
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

std::vector<char>              *Client::getMsg(int flag)
{
  int                   readed;
  std::vector<char>	*data = new std::vector<char>();
  struct sockaddr_in    infos;
  socklen_t             length = sizeof(infos);

  data->resize(SIZE_MAX_PACKET + 1);
  if ((readed = recvfrom(socket->getSocket(), data->data(), SIZE_MAX_PACKET, flag,
                         (struct sockaddr *)&infos, &length)) == -1)
    throw std::runtime_error(READ_SOCKET_ERROR);
  if (static_cast<unsigned int>(readed) < sizeof(ServerOpcodes))
    throw std::runtime_error(WRONG_PACKET);
  data->resize(readed);
  return (data);
}

ServerOpcodes			Client::getOpcode(const std::vector<char> *data) const
{
  ServerOpcodes			opcode;

  memcpy(&opcode, data->data(), sizeof(opcode));
  return (opcode);
}

static protocolFunctions protocols[NB_OPCODES] =
  {
    { CONNECT_RESPONSE, &Client::connectRecv },
	{ CHOOSEN_NAME_RESPONSE, &Client::chooseNameRecv },
	{ CREATE_POOL_RESPONSE, &Client::createPoolRecv },
	{ LIST_POOL_RESPONSE, &Client::listPoolRecv },
	{ DATA_MAP, &Client::dataMapRecv },
	{ PLAYER_JOIN_POOL, &Client::playerJoinPoolRecv },
	{ JOIN_POOL_RESPONSE, &Client::joinPoolRespRecv },
	{ PLAYER_STATUS, &Client::playerStatusRecv },
	{ PLAYER_QUIT, &Client::playerQuitRecv },
	{ LAUNCH_GAME, &Client::launchGameRecv },
	{ PLAYER_POS, &Client::playerPosRecv },
	{ ACTION, &Client::playerActionRecv },
	{ PLAYER_DIE, &Client::playerDieRecv },
	{ NEW_ENNEMY, &Client::newEnnemyRecv },
	{ END_GAME, &Client::endGameRecv },
	{ MISSILE_EXPLOSE, &Client::missileExploseRecv },
	{ ENNEMY_DIE, &Client::ennemyDieRecv },
	{ LIST_MAP_RESPONSE, &Client::listMapRecv },
	{ ENNEMY_ACTION, &Client::ennemyActionRecv },
	{ NEW_MISSILE, &Client::newMissileRecv },
    { DISCONNECT, &Client::disconnectRecv },
	{ NEXT_FRAME, &Client::nextFrameRecv },
	{ PLAYER_LIFE, &Client::playerLifeRecv },
	{ NEW_BONUS, &Client::newBonusRecv },
	{ BONUS_ERASE, &Client::deleteBonusRecv}

};

void				Client::processPacketReception()
{
  std::vector<char>		*data = getMsg(0);
  ServerOpcodes		        opcode = getOpcode(data);

  data->erase(data->begin(), data->begin() + sizeof(ServerOpcodes));
  for (int i = 0; i < NB_OPCODES; i++)
    if (protocols[i].opcode == opcode)
      (this->*(protocols[i]).protocolFunction)(data);
  delete (data);
}

void				Client::connectRecv(std::vector<char> *data)
{
  ConnectInfos			s_data;

  memcpy(&s_data, data->data(), sizeof(s_data));
  this->isConnected = s_data.isSuccess;
  this->id = s_data.id;
  if (this->isConnected == true)
  std::cout << "Connected with ip : " << id << std::endl;
}

void				Client::disconnectRecv(std::vector<char> *data)
{
  data->clear();
  this->isConnected = false;
  std::cout << "Disconnected" << std::endl;
}

void				Client::chooseNameRecv(std::vector<char> *data)
{
  ChoosenNameInfos	        s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (s_data.isSuccess == false)
    std::cout << "This name already exist !" << std::endl;
  else
  {
	  menu->setGoNextWindow(true);
	  std::cout << "Your name request was accepted" << std::endl;
  }
   
  /* faire poper une erreur a l'écran */
}

void				Client::createPoolRecv(std::vector<char> *data)
{
  CreatePoolInfos	        s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (s_data.isSuccess == false)
  {
	  std::cout << "This pool name already exist !" << std::endl;
	  return ;
  }
  this->pool = new Game(this->id, this);  
  this->menu->setGoNextWindow(true);
  this->menu->addPlayerToList(s_data.name);
  std::cout << "you created a new pool" << std::endl;
  /* change de page en fonction de la réponse */
}

void				Client::listPoolRecv(std::vector<char> *data)
{
  PoolInfos		        s_data;
  std::string			name;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  name = s_data.poolName;
  std::cout << "List pools : " << name << std::endl;
  menu->addRoomToList(name);
}

void				Client::dataMapRecv(std::vector<char> *data)
{
  DataMapInfos		        s_data;
  std::vector<std::vector<char>> map;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  map.resize(s_data.y);
  for (int y = 0; y < s_data.y; y++)
	  for (int x = 0; x < s_data.x; x++)
		  map.at(y).push_back(s_data.map[y * s_data.x + x]);
  if (pool != NULL)
	pool->setMap(map);
  std::cout << "Data map recieved !" << std::endl;
}

void				Client::playerJoinPoolRecv(std::vector<char> *data)
{
  JoinPoolInfos		        s_data;
  std::string			name;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  name = s_data.name;
  if (pool != NULL)
	pool->addPlayer(s_data.id);
  std::cout << name << " has joined the pool" << std::endl;
  menu->addPlayerToList(name);
}

void				Client::joinPoolRespRecv(std::vector<char> *data)
{
  JoinPoolRespInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (s_data.response == GAME_FULL)
    std::cout << "This pool is full" << std::endl;
  else if (s_data.response == GAME_DOESNT_EXIST)
    std::cout << "This pool doesn't exist anymore" << std::endl;
  else
  {
	  this->pool = new Game(this->id, this);
	  sendPacket(doPacket.listPlayerSnd());
	  menu->setGoNextWindow(true);
	  menu->addPlayerToList(s_data.name);
	  std::cout << "You join the pool !" << std::endl;
  }
}

void				Client::playerStatusRecv(std::vector<char> *data)
{
  StatusInfos			s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	pool->setPlayerIsReady(s_data.id, s_data.isReady);
  menu->updatePlayerStatus(s_data.name, s_data.isReady);
  std::cout << "The player with id " << s_data.id
		<< " has now the status " << s_data.isReady << std::endl;
  /* Afficher en conséquence */
}

void				Client::playerQuitRecv(std::vector<char> *data)
{
  QuitInfos			s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	pool->delPlayer(s_data.id);
  menu->delPlayerInList(s_data.name);
  menu->updatePlayerStatus(s_data.name, false);
  std::cout << "Player with id " << s_data.id << " has left the pool" << std::endl;
}

void				Client::launchGameRecv(std::vector<char> *data)
{
  data->clear();
  if (pool != NULL)
	  pool->setIsGameFinish(false);
  menu->setGoNextWindow(true);
  std::cout << "Game launched" << std::endl;
}

void				Client::playerPosRecv(std::vector<char> *data)
{
  PlayerPosInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	 pool->setPlayerPos(s_data.id, s_data.pos_x, s_data.pos_y,
					s_data.posOnCase_x, s_data.posOnCase_y);
  std::cout << "Player with id " << s_data.id << " has new coords" << std::endl;
  std::cout << s_data.pos_x << " " << s_data.pos_y << " " << s_data.posOnCase_x << " " << s_data.posOnCase_y << std::endl;
}

void				Client::playerActionRecv(std::vector<char> *data)
{
  PlayerActionInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	pool->setPlayerNextAction(s_data.id, s_data.action);
  //std::cout << "Player with id " << s_data.id << " add a new action " << s_data.action << std::endl;
}

void				Client::playerDieRecv(std::vector<char> *data)
{
  PlayerDieInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
  {
	  pool->setPlayerIsAlive(s_data.id, false);
	  this->music->playGameExplosion();
  }
  std::cout << "Player with id " << s_data.id << " died" << std::endl;
}

void				Client::newEnnemyRecv(std::vector<char> *data)
{
  NewEnnemyInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
  {
	  pool->addEnnemy(s_data.id, s_data.type);
	  pool->setEnnemyPos(s_data.id, s_data.pos_x, s_data.pos_y,
		  s_data.posOnCase_x, s_data.posOnCase_y);
  }
  std::cout << "New ennemy with id " << s_data.id << " appeared in " << std::endl;
  std::cout << s_data.pos_x << " " << s_data.pos_y << " " << s_data.posOnCase_x << " " << s_data.posOnCase_y << std::endl;
}

void				Client::endGameRecv(std::vector<char> *data)
{
  EndGameInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	pool->setIsGameFinish(true);
  if (s_data.isWin == true)
	  std::cout << "YOU WIN !" << std::endl;
  else
	  std::cout << "YOU LOOSE !" << std::endl;
  /* Afficher en fonction de si c'est une victoire ou non */
}

void				Client::missileExploseRecv(std::vector<char> *data)
{
  MissileExploseInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	  pool->addMissilesToDel(s_data.id);
  /* supprime un missile */
}

void				Client::ennemyDieRecv(std::vector<char> *data)
{
  EnnemyDieInfos		s_data;

  if (data->size() != sizeof(s_data))
    throw std::runtime_error(WRONG_PACKET);
  memcpy(&s_data, data->data(), sizeof(s_data));
  if (pool != NULL)
	  pool->addEnnemysToDel(s_data.id);
  std::cout << "Ennemy with id " << s_data.id << " died" << std::endl;
}

void				Client::listMapRecv(std::vector<char> *data)
{
	MapInfos		        s_data;
	std::string			name;

	if (data->size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, data->data(), sizeof(s_data));
	name = s_data.mapName;
	std::cout << "List map : " << name << std::endl;
	/* rajouter un nom dans le vector du menu */
}

void				Client::ennemyActionRecv(std::vector<char> *data)
{
	EnnemyActionInfos		s_data;

	if (data->size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, data->data(), sizeof(s_data));
	if (pool != NULL)
		pool->setEnnemyNextAction(s_data.id, s_data.action);
}

void				Client::newMissileRecv(std::vector<char> *data)
{
	NewMissileInfos		s_data;

	if (data->size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, data->data(), sizeof(s_data));
	this->pool->addMissile(s_data.id, s_data.idPlayer, s_data.isEnnemy,
			s_data.pos_x, s_data.pos_y, s_data.posOnCase_x, s_data.posOnCase_y, s_data.direction);
}

void				Client::nextFrameRecv(std::vector<char> *data)
{
	data->clear();
	if (pool != NULL)
		pool->setNextFrame(true);
}

void				Client::playerLifeRecv(std::vector<char> *data)
{
	PlayerLife		s_data;

	if (data->size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, data->data(), sizeof(s_data));
	if (pool->getPlayersNb() > 0)
		pool->getPlayers()[0]->setLife(s_data.life);
}

void				Client::newBonusRecv(std::vector<char> *data)
{
	NewBonus		s_data;

	if (data->size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, data->data(), sizeof(s_data));
	pool->addBonus(s_data.type, s_data.posX, s_data.posY, s_data.posOnCaseX, s_data.posOnCaseY, s_data.id);
}

void				Client::deleteBonusRecv(std::vector<char> *data)
{
	BonusErase		s_data;

	if (data->size() != sizeof(s_data))
		throw std::runtime_error(WRONG_PACKET);
	memcpy(&s_data, data->data(), sizeof(s_data));
	pool->addBonusToDel(s_data.id);
}

Music				*Client::getMusic() const
{
	return this->music;
}

void				Client::quitMenuThread()
{
	delete this->launchGui;
}