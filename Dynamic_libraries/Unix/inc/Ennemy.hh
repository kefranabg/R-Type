#ifndef						ENNEMY_HH_
# define					ENNEMY_HH_

// #include					"IEnnemy.hh"
#include					"APlayer.hh"

enum EnnemyType;


// class						Ennemy : public IEnnemy
class						Ennemy : public APlayer
{
private:
	bool					bonus;
	e_action				direction;
	EnnemyType				type;
public:
	Ennemy(int, EnnemyType);
	~Ennemy();
	virtual void			play();
	bool					getBonus() const;
	void					setDirection(e_action);
	e_action				getDirection() const;
	EnnemyType				getType() const;
};

typedef Ennemy *(*ennemy_maker)(int, EnnemyType);

#endif
