#include "Gui.hh"
#include "Client.hh"
#include "Game.hh"

Gui::Gui(Client *client, sf::RenderWindow *_window)
{
	this->client = client;
#ifdef	WIN32
	this->window = _window;
#else
	this->window = _window;
	this->window = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y), "R-TYPE");
#endif
	window->setSize(sf::Vector2u(WIN_X, WIN_Y));
	if (!this->playerTexture.loadFromFile(PLAYER_TEXTURE_PATH))
		throw std::runtime_error(ERROR_OPEN_PLAYER_TEXTURE);
	if (!this->ennemyTexture.loadFromFile(ENNEMY_TEXTURE_PATH))
		throw std::runtime_error(ERROR_OPEN_ENNEMY_TEXTURE);
	if (!this->backgroundTexture.loadFromFile(BACKGROUND_TEXTURE_PATH))
		throw std::runtime_error(ERROR_OPEN_BACKGROUND_TEXTURE);
	if (!this->playersTexture.loadFromFile(PLAYERS_TEXTURE_PATH))
		throw std::runtime_error(ERROR_OPEN_PLAYERS_TEXTURE);
	if (!this->bonusTexture.loadFromFile(BONUS_TEXTURE_PATH))
		throw std::runtime_error(ERROR_OPEN_BONUS_TEXTURE);
	this->playerMissileSprite.setTexture(this->playerTexture);
	this->playerMissileSprite.setTextureRect(sf::IntRect(PLAYER_MISSILE_OFFSET_X, PLAYER_MISSILE_OFFSET_Y, PLAYER_MISSILE_SIZE_X, PLAYER_MISSILE_SIZE_Y));
	this->ennemyMissileSprite.setTexture(this->ennemyTexture);
	this->ennemyMissileSprite.setTextureRect(sf::IntRect(ENNEMY_MISSILE_OFFSET_X, ENNEMY_MISSILE_OFFSET_Y, ENNEMY_MISSILE_SIZE_X, ENNEMY_MISSILE_SIZE_Y));
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->wallSprite.setTexture(this->ennemyTexture);
	this->wallSprite.setTextureRect(sf::IntRect(WALL_OFFSET_X, WALL_OFFSET_Y, WALL_SIZE_X, WALL_SIZE_Y));
	this->playerSprite.setTexture(this->playersTexture);
	this->ennemySprite.setTexture(this->ennemyTexture);
	this->ennemySprite.setTextureRect(sf::IntRect(ENNEMY_OFFSET_X, ENNEMY_OFFSET_Y, ENNEMY_SIZE_X, ENNEMY_SIZE_Y));
	this->lifeBonusSprite.setTexture(this->bonusTexture);
	this->lifeBonusSprite.setTextureRect(sf::IntRect(BONUSLIFE_OFFSET_X, BONUSLIFE_OFFSET_Y, BONUSLIFE_SIZE_X, BONUSLIFE_SIZE_Y));
	this->backgroundScroll = 0;
}

Gui::~Gui()
{

}

void Gui::affPlayerLife()
{
	APlayer * player = NULL;
	if (this->client->getGame()->getPlayersNb() > 0)
		player = this->client->getGame()->getPlayers()[0];
	else
		return;

	if (player->getIsAlive() == true)
	{
	  for (unsigned int i = 0; i < static_cast<unsigned int>(player->getLife()); i++)
		{
			this->lifeBonusSprite.setPosition(sf::Vector2f(i * BONUSLIFE_SIZE_X + 5, 0));
			this->window->draw(this->lifeBonusSprite);
		}
	}
}

void Gui::affBonus()
{
	float posXLimit = static_cast<float>(this->client->getGame()->getBeginLimit());
	float posOnXLimit = static_cast<float>(this->client->getGame()->getBeginLimitPrecision());
	std::vector<Bonus *> bonusList = this->client->getGame()->getBonus();

	for (unsigned int i = 0; i < bonusList.size(); i++)
	{
		float posX = static_cast<float>(bonusList[i]->getPosX());
		float posOnX = static_cast<float>(bonusList[i]->getPosOnCaseX());
		float posY = static_cast<float>(bonusList[i]->getPosY());
		float posOnY = static_cast<float>(bonusList[i]->getPosOnCaseY());
		float f = ((posX + (posOnX / 10)) - (posXLimit + (posOnXLimit / 10)));
		float f2 = (posY + (posOnY / 10));
		if (bonusList[i]->getType() == LIFE)
		{
			this->lifeBonusSprite.setPosition(sf::Vector2f((f * SPRITE_SIZE_X) - (((bonusList[i]->getSizeX() * SPRITE_SIZE_X) / 100) / 2),
				(f2 * SPRITE_SIZE_Y) - (((bonusList[i]->getSizeY() * SPRITE_SIZE_Y) / 100) / 2)));
			this->window->draw(this->lifeBonusSprite);
		}
	}
}

void Gui::affBackground()
{
	if (this->backgroundScroll == WIN_X)
		this->backgroundScroll = 0;
	this->backgroundSprite.setPosition(sf::Vector2f(-static_cast<float>(this->backgroundScroll), 0));
	this->window->draw(this->backgroundSprite);
	this->backgroundSprite.setPosition(sf::Vector2f(-static_cast<float>(this->backgroundScroll) + WIN_X, 0));
	this->window->draw(this->backgroundSprite);
}

void Gui::affMap()
{
	std::vector<std::vector<char>> map = this->client->getGame()->getMap();
	int x = this->client->getGame()->getBeginLimit();
	int posOnX = this->client->getGame()->getBeginLimitPrecision();

	for (unsigned int y = 0; y < map.size(); y++)
	{
		unsigned int tmp = 0;
		for (unsigned int count = x; count < static_cast<unsigned int >(x) + 21 && count < map[y].size(); count++)
		{
			if (map[y][count] == '1')
			{
				this->wallSprite.setPosition(sf::Vector2f((float)((tmp - ((float)posOnX / 10)) * SPRITE_SIZE_X), (float)(y * SPRITE_SIZE_Y)));
				this->window->draw(this->wallSprite);
			}
			tmp++;
		}
	}
}

void Gui::affPlayers()
{
	float posXLimit = static_cast<float>(this->client->getGame()->getBeginLimit());
	float posOnXLimit = static_cast<float>(this->client->getGame()->getBeginLimitPrecision());
	std::vector<APlayer *> playerList = this->client->getGame()->getPlayers();

	for (unsigned int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]->getIsAlive() == true)
		{
			float posX = static_cast<float>(playerList[i]->getPosX());
			float posOnX = static_cast<float>(playerList[i]->getPosOnCaseX());
			float posY = static_cast<float>(playerList[i]->getPosY());
			float posOnY = static_cast<float>(playerList[i]->getPosOnCaseY());
			float f = ((posX + (posOnX / 10)) - (posXLimit + (posOnXLimit / 10)));
			float f2 = (posY + (posOnY / 10));
			this->playerSprite.setPosition(sf::Vector2f((f * SPRITE_SIZE_X) - (((playerList[i]->getSizeX() * SPRITE_SIZE_X) / 100) / 2),
														(f2 * SPRITE_SIZE_Y) - (((playerList[i]->getSizeY() * SPRITE_SIZE_Y) / 100) / 2)));
			this->playerSprite.setTextureRect(sf::IntRect(PLAYER_OFFSET_X, PLAYER_OFFSET_Y(i), PLAYER_SIZE_X, PLAYER_SIZE_Y));
			this->window->draw(this->playerSprite);
		}
	}
}

void Gui::affEnnemies()
{
	float posXLimit = static_cast<float>(this->client->getGame()->getBeginLimit());
	float posOnXLimit = static_cast<float>(this->client->getGame()->getBeginLimitPrecision());
	std::vector<APlayer *> ennemiesList = this->client->getGame()->getEnnemys();

	for (unsigned int i = 0; i < ennemiesList.size(); i++)
	{
		float posX = static_cast<float>(ennemiesList[i]->getPosX());
		float posOnX = static_cast<float>(ennemiesList[i]->getPosOnCaseX());
		float posY = static_cast<float>(ennemiesList[i]->getPosY());
		float posOnY = static_cast<float>(ennemiesList[i]->getPosOnCaseY());
		float f = ((posX + (posOnX / 10)) - (posXLimit + (posOnXLimit / 10)));
		float f2 = (posY + (posOnY / 10));
		this->ennemySprite.setPosition(sf::Vector2f((f * SPRITE_SIZE_X) - (((ennemiesList[i]->getSizeX() * SPRITE_SIZE_X) / 100) / 2),
													(f2 * SPRITE_SIZE_Y) - (((ennemiesList[i]->getSizeY() * SPRITE_SIZE_Y) / 100) / 2)));
		if (static_cast<Ennemy *>(ennemiesList[i])->getType() == REGULAR)
			this->ennemySprite.setTextureRect(sf::IntRect(ENNEMY_SIZE_X * static_cast<Ennemy *>(ennemiesList[i])->getAnim(), ENNEMY_OFFSET_Y, ENNEMY_SIZE_X, ENNEMY_SIZE_Y));
		else
			this->ennemySprite.setTextureRect(sf::IntRect(ENNEMY_BABY_OFFSET_X, ENNEMY_BABY_OFFSET_Y, ENNEMY_BABY_SIZE_X, ENNEMY_BABY_SIZE_Y));
		this->window->draw(this->ennemySprite);
	}
}

void Gui::affMissiles()
{
	float posXLimit = static_cast<float>(this->client->getGame()->getBeginLimit());
	float posOnXLimit = static_cast<float>(this->client->getGame()->getBeginLimitPrecision());
	std::vector<Missile *> missilesList = this->client->getGame()->getMissiles();

	for (unsigned int i = 0; i < missilesList.size(); i++)
	{
		float posX = static_cast<float>(missilesList[i]->getPosX());
		float posOnX = static_cast<float>(missilesList[i]->getPosOnCaseX());
		float posY = static_cast<float>(missilesList[i]->getPosY());
		float posOnY = static_cast<float>(missilesList[i]->getPosOnCaseY());
		float f = ((posX + (posOnX / 10)) - (posXLimit + (posOnXLimit / 10)));
		float f2 = (posY + (posOnY / 10));
		if (missilesList[i]->getIsEnnemy() == false)
		{
			this->playerMissileSprite.setPosition(sf::Vector2f((f * SPRITE_SIZE_X) - (((missilesList[i]->getSizeX() * SPRITE_SIZE_X) / 100) / 2),
														(f2 * SPRITE_SIZE_Y) - (((missilesList[i]->getSizeY() * SPRITE_SIZE_Y) / 100) / 2)));
			this->window->draw(this->playerMissileSprite);
		}
		else
		{
			this->ennemyMissileSprite.setPosition(sf::Vector2f((f * SPRITE_SIZE_X) - (((missilesList[i]->getSizeX() * SPRITE_SIZE_X) / 100) / 2),
														(f2 * SPRITE_SIZE_Y) - (((missilesList[i]->getSizeY() * SPRITE_SIZE_Y) / 100) / 2)));
			this->window->draw(this->ennemyMissileSprite);
		}
	}
}

void Gui::affGame()
{
	this->window->clear();
	this->affBackground();
	this->affMap();
	this->affPlayerLife();
	this->affBonus();
	this->affPlayers();
	this->affEnnemies();
	this->affMissiles();
	this->window->display();
	this->backgroundScroll++;
}

void Gui::eventHandling()
{
	sf::Event event;

	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Resized) {
			window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		}
		if (event.type == sf::Event::Closed)
		{
			this->client->setExit(true);
			this->window->close();
			this->client->sendPacket(client->getDoPacket().disconnectSnd());
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
				this->client->getGame()->goUp();
			if (event.key.code == sf::Keyboard::Down)
				this->client->getGame()->goDown();
			if (event.key.code == sf::Keyboard::Left)
				this->client->getGame()->goLeft();
			if (event.key.code == sf::Keyboard::Right)
				this->client->getGame()->goRight();
			if (event.key.code == sf::Keyboard::Space)
				this->client->getGame()->goFire();
		}
	}
}

void Gui::aff()
{
	while (this->window->isOpen() && this->client->getGame()->getIsGameFinish() == false)
	{
		this->client->getGame()->getMutexGui().lock();
		this->eventHandling();
		this->affGame();
		this->client->getGame()->getMutexGui().unlock();
#ifdef			WIN32
		Sleep(REFRESH_TIME / 2);
#else
		usleep(REFRESH_TIME * 1000 / 2);
#endif
	}
#ifdef WIN32
	window->setSize(sf::Vector2u(800, 800));
#else
	window->close();
	delete this->window;
#endif
}
