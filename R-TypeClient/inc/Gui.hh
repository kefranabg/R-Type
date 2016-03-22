#ifndef GUI_HH_
#define	GUI_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <thread>

class Client;

#define WIN_NAME "R-Type    -   abgral_f  acca_b  thibau_v  thomps_j  raball_t"
#define WIN_X 1200
#define WIN_Y 600
#define SPRITE_SIZE_X 60
#define SPRITE_SIZE_Y 43

#ifdef WIN32
#define PLAYER_TEXTURE_PATH "../../../sprites/player.gif"
#define ENNEMY_TEXTURE_PATH "../../../sprites/ennemy.gif"
#define BACKGROUND_TEXTURE_PATH "../../../sprites/rtype-background.png"
#define PLAYERS_TEXTURE_PATH "../../../sprites/players.gif"
#define BONUS_TEXTURE_PATH "../../../sprites/bonus.png"
#else
#define PLAYER_TEXTURE_PATH "../sprites/player.gif"
#define ENNEMY_TEXTURE_PATH "../sprites/ennemy.gif"
#define BACKGROUND_TEXTURE_PATH "../sprites/rtype-background.png"
#define PLAYERS_TEXTURE_PATH "../sprites/players.gif"
#define BONUS_TEXTURE_PATH "../sprites/bonus.png"
#endif

#define ERROR_OPEN_PLAYER_TEXTURE "Could not open player.gif"
#define ERROR_OPEN_ENNEMY_TEXTURE "Could not open ennemy.gif"
#define ERROR_OPEN_BACKGROUND_TEXTURE "Could not open background.png"
#define ERROR_OPEN_PLAYERS_TEXTURE "Could not open players.gif"
#define ERROR_OPEN_BONUS_TEXTURE "Could not open bonus.png"

#define PLAYER_MISSILE_OFFSET_X 200
#define PLAYER_MISSILE_OFFSET_Y 118
#define PLAYER_MISSILE_SIZE_X 32
#define PLAYER_MISSILE_SIZE_Y 10

#define ENNEMY_MISSILE_OFFSET_X 0
#define ENNEMY_MISSILE_OFFSET_Y 120
#define ENNEMY_MISSILE_SIZE_X 32
#define ENNEMY_MISSILE_SIZE_Y 10

#define WALL_OFFSET_X 0
#define WALL_OFFSET_Y 56
#define WALL_SIZE_X SPRITE_SIZE_X
#define WALL_SIZE_Y SPRITE_SIZE_Y

#define ENNEMY_OFFSET_X 0
#define ENNEMY_OFFSET_Y 208
#define ENNEMY_SIZE_X 39
#define ENNEMY_SIZE_Y 27

#define ENNEMY_BABY_OFFSET_X 0
#define ENNEMY_BABY_OFFSET_Y 251
#define ENNEMY_BABY_SIZE_X 39
#define ENNEMY_BABY_SIZE_Y 27

#define PLAYER_OFFSET_X 100
#define PLAYER_OFFSET_Y(x) 3 + 17 * x
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 13

#define BONUSLIFE_OFFSET_X 0
#define BONUSLIFE_OFFSET_Y 0
#define BONUSLIFE_SIZE_X 30
#define BONUSLIFE_SIZE_Y 21

class Gui {
	Client *client;
	sf::RenderWindow *window;
	sf::Texture playerTexture;
	sf::Texture ennemyTexture;
	sf::Texture backgroundTexture;
	sf::Texture playersTexture;
	sf::Texture bonusTexture;
	sf::Sprite lifeBonusSprite;
	sf::Sprite playerSprite;
	sf::Sprite ennemySprite;
	sf::Sprite backgroundSprite;
	sf::Sprite playerMissileSprite;
	sf::Sprite ennemyMissileSprite;
	sf::Sprite wallSprite;
	sf::Thread *threadDisplay;
	sf::Thread *threadEvent;
	unsigned int backgroundScroll;
	unsigned int speedUp;
	unsigned int speedDown;
	unsigned int speedRight;
	unsigned int speedLeft;
	unsigned int speedSpace;
public:
	Gui(Client *, sf::RenderWindow *);
	~Gui();
	void affGame();
	void affPlayerLife();
	void affBackground();
	void affPlayers();
	void affBonus();
	void affEnnemies();
	void affMap();
	void affMissiles();
	void aff();
	void eventHandling();
};

void keyPressHandling(Client *);

#endif /* GUI_HH */