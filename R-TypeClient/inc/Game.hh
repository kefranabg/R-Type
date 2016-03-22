#ifndef						GAME_HH_
# define					GAME_HH_

#include					"Player.hh"
#include					"Ennemy.hh"
#include					"Missile.hh"
#include					"Bonus.hh"
#include					<iostream>
#include					<mutex>
#include					<vector>
#include					<thread>

/* DEFINES */

# define TIMER_WAITING_ROOM 1
# define REFRESH_TIME	25
# define REGULAR_MOOVE	1
# define ENNEMY_MOOVE	1
# define PLAYER_MOOVE	3
# define MISSILE_MOOVE	4
# define MISSILE_ENNEMY_MOOVE	1

class						Client;

class						Game
{
private:
	std::vector<APlayer *>  players;
	std::vector<APlayer *>  ennemys;
	std::vector<Missile *>	missiles;
	std::vector<Bonus *>	bonus;
	std::vector<int>		missilesToDel;
	std::vector<int>		ennemysToDel;
	std::vector<int>		bonusToDel;
	bool					isGameFinish;
	Client					*client;
	std::vector<std::vector<char>> map;
	std::thread				*launch;
	std::thread				*calcul;
	std::mutex				mutex;
	std::mutex				mutexGui;
	int						beginLimit;
	int						beginLimitPrecision;
	bool					nextFrame;
public:
	Game(int, Client *);
	~Game();
	void						setNextFrame(bool);
	int						    getPlayersNb() const;
	bool						getIsGameFinish() const;
	void						setIsGameFinish(bool);
	void						addPlayer(int);
	void						delPlayer(int);
	void						addEnnemy(int, EnnemyType);
	void						delEnnemy(int);
	void						addMissile(int, int, bool, int, int, int, int, e_action);
	void						addBonus(Type, int, int, int, int, int);
	void						delBonus(int);
	void						delMissile(int);
	void						setPlayerNextAction(int, e_action);
	void						setEnnemyNextAction(int, e_action);
	void						setPlayerIsAlive(int, bool);
	void						setPlayerIsReady(int, bool);
	void						setPlayerPos(int, int, int, int, int);
	void						setEnnemyPos(int, int, int, int, int);
	void						setMap(const std::vector<std::vector<char>> &);
	void						setPos(std::vector<APlayer *> &, int, int, int, int, int);
	void						setBeginLimit(int);
	const std::vector<std::vector<char>> &getMap() const;
	void						start();
	void						clearMap();
	void						resetPostionsPlayers();
	void						executeActions();
	int							assignMissileId();
	void						automaticMooveElements();
	void						setBeginLimitPrecision(int);
	int							getBeginLimit() const;
	int							getBeginLimitPrecision() const;
	void						goUp();
	void						goDown();
	void						goRight();
	void						goLeft();
	void						goFire();
	void						setPlayersLifes();
	std::vector<APlayer *> const &getPlayers() const;
	std::vector<APlayer *> const &getEnnemys() const;
	std::vector<Missile *> const &getMissiles() const;
	std::vector<Bonus *> const &getBonus() const;
	void						addEnnemysToDel(int);
	void						addMissilesToDel(int);
	void						addBonusToDel(int);
	void						doCalcul();
	std::mutex					&getMutexGui();
};

void							launchCalcul(Game *);
void							launchStart(Game *);

#endif 
