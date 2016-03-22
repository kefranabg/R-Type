#ifndef				 BONUS_HH_
# define			 BONUS_HH_

#include "Object.hh"

enum Type
{
	LIFE = 0
};

class			Bonus : public Object
{
private:
	Type		type;
	int			id;
public:
	Bonus(Type, int, int, int, int, int);
	~Bonus();
	Type		getType() const;
	void		setType(Type);
	int			getId() const;
	void		setId(int);
};

#endif