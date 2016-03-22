#ifndef						MISSILE_HH_
# define					MISSILE_HH_

#include					<iostream>
#include					<vector>
#include					"Object.hh"
#include					"ProtocolOpcodes.hh"

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