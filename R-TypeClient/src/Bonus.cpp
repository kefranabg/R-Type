#include			"Bonus.hh"

Bonus::Bonus(Type type, int posX, int posY, int posOnCaseX, int posOnCaseY, int id)
{
	this->id = id;
	this->type = type;
	this->posX = posX;
	this->posY = posY;
	this->posOnCaseX = posOnCaseX;
	this->posOnCaseY = posOnCaseY;
	this->sizeX = 50;
	this->sizeY = 50;
}

Bonus::~Bonus()
{

}

void			Bonus::setType(Type type)
{
	this->type = type;
}

Type			Bonus::getType() const
{
	return (this->type);
}

int			Bonus::getId() const
{
	return (this->id);
}

void		Bonus::setId(int id)
{
	this->id = id;
}

