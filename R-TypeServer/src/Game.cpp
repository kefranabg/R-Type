#include			"Game.hh"
#include			"Server.hh"

Game::Game(Server *_server, const std::string &_name, ClientInfo *player, unsigned int roomId)
{
	this->name = _name;
	this->server = _server;
	this->id = roomId;
	this->players.push_back(new Player(player, player->getId()));
	this->isGameFinish = true;
	this->beginLimit = 0;
	this->beginLimitPrecision = 0;
	this->launch = new std::thread(launchStart, this);
	this->calcul = NULL;
}

Game::~Game()
{
	delete this->launch;
	if (this->calcul != NULL)
		delete this->calcul;
}

void							launchStart(Game *game)
{
	game->start();
}

const std::string				&Game::getName() const
{
	return (this->name);
}

unsigned int								Game::getId() const
{
	return (this->id);
}

int								Game::getPlayersNb() const
{
	return (players.size());
}

void							Game::addPlayer(ClientInfo *infos)
{
	this->mutex.lock();
	players.push_back(new Player(infos, infos->getId()));
	this->mutex.unlock();
}

void							Game::delPlayer(int id)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < players.size(); i++)
	if (id == players[i]->getId())
		players.erase(players.begin() + i);
	this->mutex.unlock();
}

void							Game::addEnnemy(int id, EnnemyType type)
{
	this->mutex.lock();
	ennemys.push_back(new Ennemy(id, type));
	this->mutex.unlock();
}

void							Game::delEnnemy(int id)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < ennemys.size(); i++)
	{
		if (id == ennemys[i]->getId())
			ennemys.erase(ennemys.begin() + i);
	}
	this->mutex.unlock();
}

void							Game::setPlayerNextAction(int id, e_action action)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < players.size(); i++)
		if (id == players[i]->getId())
			players[i]->setNextAction(action);
	this->mutex.unlock();
}

void							Game::setPlayerIsAlive(int id, bool value)
{
	for (unsigned int i = 0; i < players.size(); i++)
		if (id == players[i]->getId())
		players[i]->setIsAlive(value);
}

bool							Game::getIsGameFinish() const
{
	return (this->isGameFinish);
}

void							Game::setIsGameFinish(bool value)
{
	this->isGameFinish = value;
}

void							Game::setEnnemyNextAction(int id, e_action action)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < ennemys.size(); i++)
	if (id == ennemys[i]->getId())
		ennemys[i]->setNextAction(action);
	this->mutex.unlock();
}

void							Game::setPos(std::vector<APlayer *> &list, int id, int posX, int posY,
	int posOnCaseX, int posOnCaseY)
{
	for (unsigned int i = 0; i < list.size(); i++)
	if (id == list[i]->getId())
	{
		list[i]->setPosX(posX);
		list[i]->setPosY(posY);
		list[i]->setPosOnCaseX(posOnCaseX);
		list[i]->setPosOnCaseY(posOnCaseY);
	}
}

void							Game::setPlayerPos(int id, int posX, int posY,
	int posOnCaseX, int posOnCaseY)
{
	this->setPos(players, id, posX, posY, posOnCaseX, posOnCaseY);
}

void							Game::setEnnemyPos(int id, int posX, int posY,
	int posOnCaseX, int posOnCaseY)
{
	this->setPos(ennemys, id, posX, posY, posOnCaseX, posOnCaseY);
}

void						Game::setMap(std::vector<std::vector<char>> *_map)
{
	this->map = _map;
}

std::vector<std::vector<char>> *Game::getMap() const
{
	return (this->map);
}

void						Game::setBeginLimitPrecision(int value)
{
	this->beginLimitPrecision = value;
	if (this->beginLimitPrecision >= 10)
	{
		this->beginLimitPrecision = 0;
		this->beginLimit += 1;
	}
}

void						Game::setBeginLimit(int value)
{
	this->beginLimit = value;
}

int							Game::getBeginLimit() const
{
	return (this->beginLimit);
}

int							Game::getBeginLimitPrecision() const
{
	return (this->beginLimitPrecision);
}

void						Game::addMissile(int id, int idPlayer, bool isEnnemy, int posX,
	int posY, int posOnCaseX, int posOnCaseY, e_action direction)
{
	missiles.push_back(new Missile(id, idPlayer, isEnnemy, posX, posY, posOnCaseX, posOnCaseY, direction));
}

void						Game::delMissile(int id)
{
	for (unsigned int i = 0; i < missiles.size(); i++)
	if (id == missiles[i]->getId())
		missiles.erase(missiles.begin() + i);
}

void						Game::delBonus(int id)
{
	for (unsigned int i = 0; i < bonus.size(); i++)
	if (id == bonus[i]->getId())
		bonus.erase(bonus.begin() + i);
}


bool						Game::checkAllPlayerReady() const
{
	for (unsigned int i = 0; i < players.size(); i++)
	if (static_cast<Player *>(players[i])->getClientInfo()->getIsReady() == false)
		return (false);
	return (true);
}

bool						Game::checkAllPlayerAreDead() const
{
	for (unsigned int i = 0; i < players.size(); i++)
	if (players[i]->getIsAlive() == true)
		return (false);
	return (true);
}

bool						Game::checkAllPlayerReadyToGame() const
{
	for (unsigned int i = 0; i < players.size(); i++)
	if (static_cast<Player *>(players[i])->getClientInfo()->getIsReadyToGame() == false)
		return (false);
	return (true);
}

void						Game::assignPositions()
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->setPosX(0);
		players[i]->setPosY(i * 3 + 2);
		players[i]->setPosOnCaseX(5);
		players[i]->setPosOnCaseY(5);
		for (unsigned int y = 0; y < players.size(); y++)
		server->sendPacket(server->getDoPacket().playerPosSnd(players[i]->getId(), 0, i * 3 + 2, 5, 5),
			static_cast<Player *>(players[y])->getClientInfo()->getAddr());
	}
}

void						Game::resetAllPlayers()
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->setIsAlive(true);
		players[i]->clearActions();
		static_cast<Player *>(players[i])->getClientInfo()->setIsReady(false);
		static_cast<Player *>(players[i])->getClientInfo()->setIsReadyToGame(false);
	}
}

void						Game::automaticMooveElements()
{
	for (unsigned int i = 0; i < players.size(); i++)
		players[i]->setPosOnCaseX(players[i]->getPosOnCaseX() + REGULAR_MOOVE);
	for (unsigned int i = 0; i < missiles.size(); i++)
	{
		if (missiles[i]->getDirection() == RIGHT)
			missiles[i]->setPosOnCaseX(missiles[i]->getPosOnCaseX() + REGULAR_MOOVE + MISSILE_MOOVE);
		if (missiles[i]->getDirection() == LEFT)
			missiles[i]->setPosOnCaseX(missiles[i]->getPosOnCaseX() - MISSILE_ENNEMY_MOOVE);
	}
}

int						Game::assignMissileId()
{
	bool			check;

	for (int tmp_id = 0; tmp_id < 1000; tmp_id++)
	{
		check = true;
		for (unsigned int i = 0; i < missiles.size(); i++)
		  if (tmp_id == missiles[i]->getId())
				check = false;
		if (check == true)
			return (tmp_id);
	}
	return (-1);
}

int						Game::assignEnnemyId()
{
	bool			check;

	for (int tmp_id = 0; tmp_id < 1000; tmp_id++)
	{
		check = true;
		for (unsigned int i = 0; i < ennemys.size(); i++)
		if (tmp_id == ennemys[i]->getId())
			check = false;
		if (check == true)
			return (tmp_id);		
	}
	return (-1);
}

int						Game::assignBonusId()
{
	bool			check;

	for (int tmp_id = 0; tmp_id < 1000; tmp_id++)
	{
		check = true;
		for (unsigned int i = 0; i < bonus.size(); i++)
		if (tmp_id == bonus[i]->getId())
			check = false;
		if (check == true)
			return (tmp_id);
	}
	return (-1);
}

void						Game::executeActions()
{
	e_action				missileDirection;
	bool					isEnnemy;

	this->mutex.lock();
	for (unsigned int i = 0; i < players.size(); i++)
		while (players[i]->getActionListSize() > 0)
		{
			if (players[i]->getNextAction() == RIGHT)
				players[i]->setPosOnCaseX(players[i]->getPosOnCaseX() + PLAYER_MOOVE);
			else if (players[i]->getNextAction() == LEFT)
				players[i]->setPosOnCaseX(players[i]->getPosOnCaseX() - PLAYER_MOOVE);
			else if (players[i]->getNextAction() == UP)
				players[i]->setPosOnCaseY(players[i]->getPosOnCaseY() - PLAYER_MOOVE);
			else if (players[i]->getNextAction() == DOWN)
				players[i]->setPosOnCaseY(players[i]->getPosOnCaseY() + PLAYER_MOOVE);
			else
			{
				if (players[i]->getIsEnnemy() == true)
				{
					missileDirection = LEFT;
					isEnnemy = true;
				}
				else
				{
					missileDirection = RIGHT;
					isEnnemy = false;
				}
				int missileId = assignMissileId();
					addMissile(missileId, players[i]->getId(), isEnnemy, players[i]->getPosX() + 1,
					players[i]->getPosY(), 5, players[i]->getPosOnCaseY(), missileDirection);
				for (unsigned int y = 0; y < players.size(); y++)
					server->sendPacket(server->getDoPacket().newMissileSnd(missileId,
										       players[i]->getId(), isEnnemy, players[i]->getPosX() + 1,
										       players[i]->getPosY(), 5, players[i]->getPosOnCaseY(), missileDirection),
					static_cast<Player *>(players[y])->getClientInfo()->getAddr());
			}
			players[i]->delFirstAction();
		}
		for (unsigned int i = 0; i < ennemys.size(); i++)
		while (ennemys[i]->getActionListSize() > 0)
		{
			if (ennemys[i]->getNextAction() == RIGHT)
				ennemys[i]->setPosOnCaseX(ennemys[i]->getPosOnCaseX() + ENNEMY_MOOVE);
			else if (ennemys[i]->getNextAction() == LEFT)
				ennemys[i]->setPosOnCaseX(ennemys[i]->getPosOnCaseX() - ENNEMY_MOOVE);
			else if (ennemys[i]->getNextAction() == UP)
				ennemys[i]->setPosOnCaseY(ennemys[i]->getPosOnCaseY() - ENNEMY_MOOVE);
			else if (ennemys[i]->getNextAction() == DOWN)
				ennemys[i]->setPosOnCaseY(ennemys[i]->getPosOnCaseY() + ENNEMY_MOOVE);
			else
			{
				if (ennemys[i]->getIsEnnemy() == true)
				{
					missileDirection = LEFT;
					isEnnemy = true;
				}
				else
				{
					missileDirection = RIGHT;
					isEnnemy = false;
				}
				int missileId = assignMissileId();
				addMissile(missileId, ennemys[i]->getId(), isEnnemy, ennemys[i]->getPosX() - 1,
					ennemys[i]->getPosY(), 5, ennemys[i]->getPosOnCaseY(), missileDirection);
				for (unsigned int y = 0; y < players.size(); y++)
					server->sendPacket(server->getDoPacket().newMissileSnd(missileId,
					ennemys[i]->getId(), isEnnemy, ennemys[i]->getPosX() - 1,
					ennemys[i]->getPosY(), 5, ennemys[i]->getPosOnCaseY(), missileDirection),
					static_cast<Player *>(players[y])->getClientInfo()->getAddr());
			}
			ennemys[i]->delFirstAction();
		}
		this->mutex.unlock();
}

void						Game::checkEnnemysAndMissilesPostion()
{
	for (unsigned int i = 0; i < missiles.size(); i++)
	if (missiles[i]->getPosX() * 100 + missiles[i]->getPosOnCaseX() * 10 + missiles[i]->getSizeX() / 2 
			> getBeginLimit() * 100 + getBeginLimitPrecision() + 2000
			|| missiles[i]->getPosX() * 100 + missiles[i]->getPosOnCaseX() * 10 - missiles[i]->getSizeX() / 2
				< getBeginLimit() * 100 + getBeginLimitPrecision() * 10)
	{
		for (unsigned int y = 0; y < players.size(); y++)
			server->sendPacket(server->getDoPacket().missileExploseSnd(missiles[i]->getId()),
			static_cast<Player *>(players[y])->getClientInfo()->getAddr());
		delMissile(missiles[i]->getId());
	}
	for (unsigned int i = 0; i < ennemys.size(); i++)
	if (ennemys[i]->getPosX() * 100 + ennemys[i]->getPosOnCaseX() * 10 - ennemys[i]->getSizeX() / 2
	< getBeginLimit() * 100 + getBeginLimitPrecision() * 10)
	{
		for (unsigned int y = 0; y < players.size(); y++)
			server->sendPacket(server->getDoPacket().missileExploseSnd(ennemys[i]->getId()),
			static_cast<Player *>(players[y])->getClientInfo()->getAddr());
		delEnnemy(ennemys[i]->getId());
	}
	for (unsigned int i = 0; i < bonus.size(); i++)
	if (bonus[i]->getPosX() * 100 + bonus[i]->getPosOnCaseX() * 10 - bonus[i]->getSizeX() / 2
		< getBeginLimit() * 100 + getBeginLimitPrecision() * 10)
	{
		for (unsigned int y = 0; y < players.size(); y++)
			server->sendPacket(server->getDoPacket().missileExploseSnd(bonus[i]->getId()),
			static_cast<Player *>(players[y])->getClientInfo()->getAddr());
		delBonus(bonus[i]->getId());
	}
}

void						Game::goUp(APlayer *player)
{
	for (unsigned int y = 0; y < players.size(); y++)
		server->sendPacket(server->getDoPacket().ennemyActionSnd(player->getId(), UP),
		static_cast<Player *>(players[y])->getClientInfo()->getAddr());
	player->setNextAction(UP);
}

void						Game::goDown(APlayer *player)
{
	for (unsigned int y = 0; y < players.size(); y++)
		server->sendPacket(server->getDoPacket().ennemyActionSnd(player->getId(), DOWN),
		static_cast<Player *>(players[y])->getClientInfo()->getAddr());
	player->setNextAction(DOWN);
}

void						Game::goRight(APlayer *player)
{
	for (unsigned int y = 0; y < players.size(); y++)
		server->sendPacket(server->getDoPacket().ennemyActionSnd(player->getId(), RIGHT),
		static_cast<Player *>(players[y])->getClientInfo()->getAddr());
	player->setNextAction(RIGHT);
}

void						Game::goLeft(APlayer *player)
{
	for (unsigned int y = 0; y < players.size(); y++)
		server->sendPacket(server->getDoPacket().ennemyActionSnd(player->getId(), LEFT),
		static_cast<Player *>(players[y])->getClientInfo()->getAddr());
	player->setNextAction(LEFT);
}

void						Game::goFire(APlayer *player)
{
	if (this->missiles.size() >= 100)
		return ;
	for (unsigned int y = 0; y < players.size(); y++)
		server->sendPacket(server->getDoPacket().ennemyActionSnd(player->getId(), FIRE),
		static_cast<Player *>(players[y])->getClientInfo()->getAddr());
	player->setNextAction(FIRE);
}

void						Game::checkElementsPosition()
{
	this->mutex.lock();
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (static_cast<unsigned int>(players[i]->getPosX()) < map->at(0).size()
				&& map->at(players[i]->getPosY()).at(players[i]->getPosX()) == '1')
		{
			for (unsigned int count = 0; count < players.size(); count++)
				server->sendPacket(server->getDoPacket().playerDieSnd(players[i]->getId()),
				static_cast<Player *>(players[count])->getClientInfo()->getAddr());
			players[i]->setIsAlive(false);
		}
	}
	for (unsigned int i = 0; i < missiles.size(); i++)
	{
		if (static_cast<unsigned int>(missiles[i]->getPosX()) < map->at(0).size() && missiles[i]->getPosX() > 0 &&
			i < missiles.size() && map->at(missiles[i]->getPosY()).at(missiles[i]->getPosX()) == '1')
		{
			for (unsigned int y = 0; y < players.size(); y++)
				server->sendPacket(server->getDoPacket().missileExploseSnd(missiles[i]->getId()),
				static_cast<Player *>(players[y])->getClientInfo()->getAddr());
			delMissile(missiles[i]->getId());
		}
	}
	this->mutex.unlock();
}

void						Game::start()
{	
	while (true)
	{
		// Loop of the waiting room
		while (checkAllPlayerReady() == false || players.size() == 0)
		{
#ifdef			WIN32
			Sleep(TIMER_WAITING_ROOM * 1000);
#else
			sleep(TIMER_WAITING_ROOM);
#endif
		}

		// Prepare the Game
		std::cout << "Game will start" << std::endl;
		setIsGameFinish(false);
		for (unsigned int i = 0; i < players.size(); i++)
		server->sendPacket(server->getDoPacket().dataMapSnd(map),
			static_cast<Player *>(players[i])->getClientInfo()->getAddr());

		// Game initialization
		assignPositions();
		resetAllPlayers();
		setPlayersLifes();
		while (checkAllPlayerReadyToGame() == false);
		for (unsigned int i = 0; i < players.size(); i++)
			server->sendPacket(server->getDoPacket().launchGameSnd(),
			static_cast<Player *>(players[i])->getClientInfo()->getAddr());

		// Loop of the game
		while (getIsGameFinish() == false)
		{
			// If all the players are dead, send to all client the end of game
			this->calcul = new std::thread(launchCalcul, this);

			for (unsigned int count = 0; count < players.size(); count++)
				server->sendPacket(server->getDoPacket().nextFrameSnd(),
				static_cast<Player *>(players[count])->getClientInfo()->getAddr());
#ifdef			WIN32
			Sleep(REFRESH_TIME);
#else
			usleep(REFRESH_TIME * 1000);
#endif
			this->calcul->join();
		}
		missiles.clear();
		ennemys.clear();
		bonus.clear();
		setBeginLimitPrecision(0);
		setBeginLimit(0);
	}
	return;
}

void launchCalcul(Game *game)
{
	game->doCalcul();
}

void Game::doCalcul()
{	
	srand(static_cast<int>(clock()));

	// Check if all players are alives
	if (checkAllPlayerAreDead() == true)
	{
		for (unsigned int i = 0; i < players.size(); i++)
			server->sendPacket(server->getDoPacket().endGameSnd(false),
			static_cast<Player *>(players[i])->getClientInfo()->getAddr());
		setIsGameFinish(true);
	}
	else
	{
		// Check if Missile explose or Ennemy die
		checkEnnemysAndMissilesPostion();

		// Check if Elements are in the wall
		checkElementsPosition();

		// Moove all elements automaticly each loop
		automaticMooveElements();

		// Execute player's actions
		executeActions();

		//Random ennemys apparition
		if (rand() % 30 == 0 && this->ennemys.size() < 7)
			randomEnnemysApparition();

		// Ennemys action
		doEnnemysAction();

		// Check collisions
		checkCollisions();

		// Increase the limit
		if (getBeginLimit() < static_cast<int>(map->at(0).size()) - 20)
			setBeginLimitPrecision(getBeginLimitPrecision() + REGULAR_MOOVE);
	}
}


void						Game::randomEnnemysApparition()
{
	int posY = rand() % 13;

	if (map->at(posY).at(getBeginLimit() + 19) != '1')
	{
		int id = assignEnnemyId();
		EnnemyType type = static_cast<EnnemyType>(rand() % 2);
		addEnnemy(id, type);
		setEnnemyPos(id, getBeginLimit() + 19, posY + 1, 5, 5);
		for (unsigned int i = 0; i < players.size(); i++)
			server->sendPacket(server->getDoPacket().newEnnemySnd(id, getBeginLimit() + 19, posY + 1, 5, 5, type),
			static_cast<Player *>(players[i])->getClientInfo()->getAddr());
	}
}

void						Game::doEnnemysAction()
{
	for (unsigned int i = 0; i < ennemys.size(); i++)
	if (rand() % 50 == 0 && static_cast<Ennemy *>(ennemys[i])->getType() == REGULAR)
		goFire(ennemys[i]);
	else
	{
		//Moove ennemys
		if (static_cast<Ennemy *>(ennemys[i])->getType() == REGULAR)
		{
			if (ennemys[i]->getPosY() - 1 >= 0 && map->at(ennemys[i]->getPosY() - 1).at(ennemys[i]->getPosX()) != '1'
				&& static_cast<Ennemy *>(ennemys[i])->getDirection() == UP)
				goUp(ennemys[i]);
			else if (static_cast<unsigned int>(ennemys[i]->getPosY() + 1) < map->size()
				&& map->at(ennemys[i]->getPosY() + 1).at(ennemys[i]->getPosX()) != '1'
				&& static_cast<Ennemy *>(ennemys[i])->getDirection() == DOWN)
				goDown(ennemys[i]);
			else
			{
				if (static_cast<Ennemy *>(ennemys[i])->getDirection() == UP)
					static_cast<Ennemy *>(ennemys[i])->setDirection(DOWN);
				else
					static_cast<Ennemy *>(ennemys[i])->setDirection(UP);
			}
		}
		else
			goLeft(ennemys[i]);
	}
}

void						Game::checkCollisions()
{
	// Check Ennemys collision with missiles 
	for (unsigned int i = 0; i < ennemys.size(); i++)
	{
		for (unsigned int y = 0; y < missiles.size(); y++)
		if (i < ennemys.size() && ennemys[i]->checkCollision(missiles[y]) == true)
		{
			ennemys[i]->setLife(ennemys[i]->getLife() - 1);
			if (ennemys[i]->getLife() < 1)
			{
				if (rand() % 8 == 0)
				{
					int bonusId = assignBonusId();
					bonus.push_back(new Bonus(LIFE, ennemys[i]->getPosX(), ennemys[i]->getPosY(),
					ennemys[i]->getPosOnCaseX(), ennemys[i]->getPosOnCaseY(), bonusId));
					for (unsigned int count = 0; count < players.size(); count++)
						server->sendPacket(server->getDoPacket().newBonusSnd(LIFE, ennemys[i]->getPosX(), ennemys[i]->getPosY(),
						ennemys[i]->getPosOnCaseX(), ennemys[i]->getPosOnCaseY(), bonusId),
						static_cast<Player *>(players[count])->getClientInfo()->getAddr());
				}
					
				for (unsigned int count = 0; count < players.size(); count++)
					server->sendPacket(server->getDoPacket().ennemyDieSnd(ennemys[i]->getId()),
					static_cast<Player *>(players[count])->getClientInfo()->getAddr());
				delEnnemy(ennemys[i]->getId());
			}
 		}
	}

	for (unsigned int i = 0; i < players.size(); i++)
	{
		// Check Players collision with missiles
		for (unsigned int y = 0; y < missiles.size(); y++)
		if (players[i]->checkCollision(missiles[y]) == true)
		{
			players[i]->setLife(players[i]->getLife() - 1);
			server->sendPacket(server->getDoPacket().playerLifeSnd(players[i]->getLife()),
				static_cast<Player *>(players[i])->getClientInfo()->getAddr());
			if (players[i]->getLife() < 1)
			{
				for (unsigned int count = 0; count < players.size(); count++)
					server->sendPacket(server->getDoPacket().playerDieSnd(players[i]->getId()),
					static_cast<Player *>(players[count])->getClientInfo()->getAddr());
				players[i]->setIsAlive(false);
			}

			for (unsigned int count = 0; count < players.size(); count++)
				server->sendPacket(server->getDoPacket().missileExploseSnd(missiles[y]->getId()),
				static_cast<Player *>(players[count])->getClientInfo()->getAddr());
			delMissile(missiles[y]->getId());
		}

		// Check Players collision with ennemys
		for (unsigned int y = 0; y < ennemys.size(); y++)
		if (y < ennemys.size() && players[i]->checkCollision(ennemys[y]) == true)
		{
			players[i]->setLife(players[i]->getLife() - 1);
			server->sendPacket(server->getDoPacket().playerLifeSnd(players[i]->getLife()),
				static_cast<Player *>(players[i])->getClientInfo()->getAddr());
			if (players[i]->getLife() < 1)
			{
				for (unsigned int count = 0; count < players.size(); count++)
					server->sendPacket(server->getDoPacket().playerDieSnd(players[i]->getId()),
					static_cast<Player *>(players[count])->getClientInfo()->getAddr());
				players[i]->setIsAlive(false);
			}

			ennemys[y]->setLife(ennemys[y]->getLife() - 1);
			if (ennemys[y]->getLife() < 1)
			{
				for (unsigned int count = 0; count < players.size(); count++)
					server->sendPacket(server->getDoPacket().ennemyDieSnd(ennemys[y]->getId()),
					static_cast<Player *>(players[count])->getClientInfo()->getAddr());
				delEnnemy(ennemys[y]->getId());
			}
		}

		// Check Players collision with Bonus
		
		for (unsigned int y = 0; y < bonus.size(); y++)
		if (y < bonus.size() && players[i]->checkCollision(bonus[y]) == true)
		{
			if (players[i]->checkCollision(bonus[y]) == true)
			if (bonus[y]->getType() == LIFE)
			{
				if (players[i]->getLife() < 3)
					players[i]->setLife(players[i]->getLife() + 1);
				server->sendPacket(server->getDoPacket().playerLifeSnd(players[i]->getLife()),
					static_cast<Player *>(players[i])->getClientInfo()->getAddr());
				for (unsigned int count = 0; count < players.size(); count++)
					server->sendPacket(server->getDoPacket().deleteBonusSnd(bonus[y]->getId()),
					static_cast<Player *>(players[count])->getClientInfo()->getAddr());
				delBonus(bonus[y]->getId());
			}
		}
	}
}

void					Game::setPlayersLifes()
{
	for (unsigned int i = 0; i < players.size(); i++)
		players[i]->setLife(3);
}