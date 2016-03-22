#ifndef						GAME_HH_
# define					GAME_HH_

#ifdef						WIN32
#include					"WinThread.hh"
#else
#include					"UnixThread.hh"
#endif

#include					"IThread.hh"
#include					"Player.hh"
#include					"Ennemy.hh"
#include					"Missile.hh"
#include					"Bonus.hh"
#include					<time.h>
#include					<iostream>
#include					<vector>
#include					<mutex>
#include					<thread>

/* DEFINES */

# define TIMER_WAITING_ROOM 1
# define REFRESH_TIME	25
# define REGULAR_MOOVE	1
# define ENNEMY_MOOVE	1
# define PLAYER_MOOVE	3
# define MISSILE_MOOVE	4
# define MISSILE_ENNEMY_MOOVE	1

class						Server;

class						Game
{
private:
	Server					*server;
	std::string				name;
	unsigned int			id;
	std::vector<APlayer *>  players;
	std::vector<APlayer *>  ennemys;
	std::vector<Missile *>	missiles;
	std::vector<Bonus *>	bonus;
	bool					isGameFinish;
	std::vector<std::vector<char>> *map;
	std::thread				*launch;
	std::thread				*calcul;
	int						beginLimit;
	int						beginLimitPrecision;
	std::mutex				mutex;
public:
	Game(Server *, const std::string &, ClientInfo *, unsigned int);
	~Game();
	const std::string			&getName() const;
	unsigned int							getId() const;
	int						    getPlayersNb() const;
	bool						getIsGameFinish() const;
	void						setIsGameFinish(bool);
	void						addPlayer(ClientInfo *);
	void						delPlayer(int);
	void						addEnnemy(int, EnnemyType);
	void						delEnnemy(int);
	void						addMissile(int, int, bool, int, int, int, int, e_action);
	void						delMissile(int);
	void						delBonus(int);
	void						setPlayerNextAction(int, e_action);
	void						setPlayerIsAlive(int, bool);
	void						setEnnemyNextAction(int, e_action);
	void						setPlayerPos(int, int, int, int, int);
	void						setEnnemyPos(int, int, int, int, int);
	void						setMap(std::vector<std::vector<char>> *);
	void						setPos(std::vector<APlayer *> &, int, int, int, int, int);
	void						setBeginLimit(int);
	std::vector<std::vector<char>> *getMap() const;
	bool						checkAllPlayerReady() const;
	bool						checkAllPlayerReadyToGame() const;
	bool						checkAllPlayerAreDead() const;
	void						assignPositions();
	void						resetAllPlayers();
	void						start();
	void						automaticMooveElements();
	void						executeActions();
	int							assignMissileId();
	int							assignBonusId();
	int							assignEnnemyId();
	void						checkElementsPosition();
	void						checkEnnemysAndMissilesPostion();
	void						setBeginLimitPrecision(int);
	int							getBeginLimit() const;
	int							getBeginLimitPrecision() const;
	void						goUp(APlayer *);
	void						goDown(APlayer *);
	void						goRight(APlayer *);
	void						goLeft(APlayer *);
	void						goFire(APlayer *);
	void						doCalcul();
	void						randomEnnemysApparition();
	void						doEnnemysAction();
	void						checkCollisions();
	void						setPlayersLifes();
};

void							launchCalcul(Game *);
void							launchStart(Game *);

#endif
