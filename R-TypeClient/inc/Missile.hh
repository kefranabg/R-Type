#ifndef						MISSILE_HH_
# define					MISSILE_HH_

#include					"ProtocolOpcodes.hh"
#include					"Object.hh"
#include					<iostream>

class						Missile : public Object
{
private:
	int					id;
	int					idPlayer;
	bool				isEnnemy;
	e_action			direction;
public:
	Missile(int, int, bool, int, int, int, int, e_action);
	~Missile();
	int					getId() const;
	int					getIdPlayer() const;
	bool				getIsEnnemy() const;
	e_action			getDirection() const;
	void				setDirection(e_action);
};

#endif