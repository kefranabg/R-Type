#ifndef						ENNEMY_HH_
# define					ENNEMY_HH_

#include					"APlayer.hh"

enum EnnemyType;

class						Ennemy : public APlayer
{
private:
	bool					bonus;
	EnnemyType				type;
	int						anim;
public:
	Ennemy(int, EnnemyType);
	~Ennemy();
	virtual void			play();
	bool					getBonus() const;
	EnnemyType				getType() const;
	int						getAnim() const;
	void					changeAnim();
};

#endif