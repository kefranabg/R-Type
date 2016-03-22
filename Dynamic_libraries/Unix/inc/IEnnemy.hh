#ifndef						IENNEMY_HH_
# define					IENNEMY_HH_

#include					"APlayer.hh"

enum EnnemyType;


class						IEnnemy : public APlayer
{
public:
  virtual ~IEnnemy();
	// virtual void			play() = 0;
	// virtual bool					getBonus() const = 0;
	// virtual void					setDirection(e_action) = 0;
	// virtual e_action				getDirection() const = 0;
	// virtual EnnemyType				getType() const = 0;

};

#endif
