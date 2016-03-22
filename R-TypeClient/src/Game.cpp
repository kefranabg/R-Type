#include			"Game.hh"
#include			"Client.hh"

Game::Game(int idPlayer, Client *_client)
{
	this->players.push_back(new Player(idPlayer));
	this->isGameFinish = true;
	this->client = _client;
	this->beginLimit = 0;
	this->beginLimitPrecision = 0;
	this->launch = new std::thread(launchStart, this);
	this->calcul = NULL;
	this->nextFrame = false;
}

Game::~Game()
{
	delete this->launch;
	if (this->calcul != NULL)
		delete this->calcul;
}

void						Game::setNextFrame(bool value)
{
	this->nextFrame = value;
}

std::vector<Bonus *> const &Game::getBonus() const
{
	return (this->bonus);
}

std::vector<APlayer *> const &Game::getPlayers() const
{
	return (this->players);
}

std::vector<APlayer *> const &Game::getEnnemys() const
{
	return (this->ennemys);
}

std::vector<Missile *> const &Game::getMissiles() const
{
	return (this->missiles);
}

void							launchStart(Game *game)
{
	game->start();
}

int								Game::getPlayersNb() const
{
	return (players.size());
}

void							Game::addPlayer(int id)
{
	this->mutex.lock();
	players.push_back(new Player(id));
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
		if (id == ennemys[i]->getId())
			ennemys.erase(ennemys.begin() + i);
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

void							Game::setEnnemyNextAction(int id, e_action action)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < ennemys.size(); i++)
	if (id == ennemys[i]->getId())
		ennemys[i]->setNextAction(action);
	this->mutex.unlock();
}

void							Game::setPlayerIsAlive(int id, bool value)
{
	for (unsigned int i = 0; i < players.size(); i++)
		if (id == players[i]->getId())
		players[i]->setIsAlive(value);
}

void							Game::setPlayerIsReady(int id, bool value)
{
	for (unsigned int i = 0; i < players.size(); i++)
	if (id == players[i]->getId())
		static_cast<Player *>(players[i])->setIsReady(value);
}

bool							Game::getIsGameFinish() const
{
	return (this->isGameFinish);
}

void							Game::setIsGameFinish(bool value)
{
	this->isGameFinish = value;
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

void						Game::setMap(const std::vector<std::vector<char>> &_map)
{
	this->map = _map;
}

const std::vector<std::vector<char>> &Game::getMap() const
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

int							Game::getBeginLimit() const
{
	return (this->beginLimit);
}

int							Game::getBeginLimitPrecision() const
{
	return (this->beginLimitPrecision);
}

std::mutex					&Game::getMutexGui()
{
	return (this->mutexGui);
}

void						Game::addMissile(int id, int idPlayer, bool isEnnemy, int posX,
											int posY, int posOnCaseX, int posOnCaseY, e_action direction)
{
	missiles.push_back(new Missile(id, idPlayer, isEnnemy, posX, posY, posOnCaseX, posOnCaseY, direction));
}

void						Game::setBeginLimit(int value)
{
	this->beginLimit = value;
}

void						Game::delMissile(int id)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < missiles.size(); i++)
	if (id == missiles[i]->getId())
		missiles.erase(missiles.begin() + i);
	this->mutex.unlock();
}


void						Game::addBonus(Type type, int posX, int posY, int posOnCaseX, int posOnCaseY, int id)
{
	bonus.push_back(new Bonus(type, posX, posY, posOnCaseX, posOnCaseY, id));
}

void						Game::delBonus(int id)
{
	this->mutex.lock();
	for (unsigned int i = 0; i < bonus.size(); i++)
	if (id == bonus[i]->getId())
		bonus.erase(bonus.begin() + i);
	this->mutex.unlock();
}

void						Game::resetPostionsPlayers()
{
	for (unsigned int i = 0; i < players.size(); i++)
		players[i]->resetPositions();
}

void						Game::addEnnemysToDel(int id)
{
	ennemysToDel.push_back(id);
}

void						Game::addMissilesToDel(int id)
{
	missilesToDel.push_back(id);
}

void						Game::addBonusToDel(int id)
{
	bonusToDel.push_back(id);
}

void						Game::executeActions()
{
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
		ennemys[i]->delFirstAction();
	}
	this->mutex.unlock();
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

void						Game::goUp()
{
	if (players[0]->getIsAlive() == false)
		return;
	if (players[0]->getPosOnCaseY() - players[0]->getSizeY() / 10 / 2 - PLAYER_MOOVE < 0
		&& map[players[0]->getPosY() - 1][players[0]->getPosX()] == '1')
	{
		players[0]->setIsAlive(false);
		client->sendPacket(client->getDoPacket().playerDieSnd());
		return ;
	}
	players[0]->setNextAction(UP);
	client->sendPacket(client->getDoPacket().playerActionSnd(UP));
}

void						Game::goDown()
{
	if (players[0]->getIsAlive() == false)
		return;
	if (players[0]->getPosOnCaseY() + players[0]->getSizeY() / 10 / 2 + PLAYER_MOOVE > 10
		&& map[players[0]->getPosY() + 1][players[0]->getPosX()] == '1')
	{
		players[0]->setIsAlive(false);
		client->sendPacket(client->getDoPacket().playerDieSnd());
		return;
	}
	players[0]->setNextAction(DOWN);
	client->sendPacket(client->getDoPacket().playerActionSnd(DOWN));
}

void						Game::goRight()
{
	if (players[0]->getIsAlive() == false)
		return;
	if (players[0]->getPosX() * 100 + players[0]->getPosOnCaseX() + players[0]->getSizeX() / 2
			+ PLAYER_MOOVE > getBeginLimit() * 100 + getBeginLimitPrecision() + 2000)
		return;
	players[0]->setNextAction(RIGHT);
	client->sendPacket(client->getDoPacket().playerActionSnd(RIGHT));
}

void						Game::goLeft()
{
	if (players[0]->getIsAlive() == false)
		return;
	if (players[0]->getPosX() * 100 + players[0]->getPosOnCaseX() - players[0]->getSizeX() / 2
			- PLAYER_MOOVE < getBeginLimit() * 100 + getBeginLimitPrecision())
		return ;
	players[0]->setNextAction(LEFT);
	client->sendPacket(client->getDoPacket().playerActionSnd(LEFT));
}

void						Game::goFire()
{
	if (players[0]->getIsAlive() == false)
		return;
	players[0]->setNextAction(FIRE);
	client->sendPacket(client->getDoPacket().playerActionSnd(FIRE));
}


void						Game::start()
{
	while (true)
	{
		// Reset data
		map.clear();
		resetPostionsPlayers();
		setPlayersLifes();

		// Waiting for the server initialisation
		while (map.size() == 0 || players[0]->getPosX() == -1)
		{
#ifdef			WIN32
			Sleep(TIMER_WAITING_ROOM * 1000);
#else
			sleep(TIMER_WAITING_ROOM);
#endif
		}
		std::cout << "Send readyToGame to server" << std::endl;
		client->sendPacket(client->getDoPacket().readyToGameSnd());

		// Wait for all players
		while (getIsGameFinish() == true)
			std::cout << "waiting for players" << std::endl;

		this->client->getMusic()->playGameTheme();
		// Game boucle
		while (getIsGameFinish() == false)
		{
			this->mutexGui.lock();
			this->calcul = new std::thread(launchCalcul, this);
			this->mutexGui.unlock();
			this->calcul->join();
			while (nextFrame == false && getIsGameFinish() == false);
			nextFrame = false;
		}
		this->client->getMusic()->stopGameTheme();
		missiles.clear();
		ennemys.clear();
		bonus.clear();
		setBeginLimit(0);
		setBeginLimitPrecision(0);
		for (unsigned int i = 0; i < players.size(); i++)
		{
			players[i]->setIsAlive(true);
			players[i]->clearActions();
		}
	}

}

void launchCalcul(Game *game)
{
	game->doCalcul();
}

void Game::doCalcul()
{
	// Moove all elements automaticly each loop
	automaticMooveElements();

	// Execute player's actions
	executeActions();

	// Increase the limit
	if (getBeginLimit() < static_cast<int>(map[0].size()) - 20)
		setBeginLimitPrecision(getBeginLimitPrecision() + REGULAR_MOOVE);

	// Check if player finish the lvl
	for (unsigned int i = 0; i < players.size(); i++)
		if (static_cast<unsigned int>(players[i]->getPosX()) == map[0].size())
			client->sendPacket(client->getDoPacket().playerFinishSnd());

	// Del elems
	for (unsigned int i = 0; i < missilesToDel.size(); i++)
		delMissile(missilesToDel[i]);
	missilesToDel.clear();
	for (unsigned int i = 0; i < ennemysToDel.size(); i++)
		delEnnemy(ennemysToDel[i]);
	ennemysToDel.clear();
	for (unsigned int i = 0; i < bonusToDel.size(); i++)
		delBonus(bonusToDel[i]);
	bonusToDel.clear();

	for (unsigned int i = 0; i < ennemys.size(); i++)
		static_cast<Ennemy *>(ennemys[i])->changeAnim();

}

void					Game::setPlayersLifes()
{
	for (unsigned int i = 0; i < players.size(); i++)
		players[i]->setLife(3);
}