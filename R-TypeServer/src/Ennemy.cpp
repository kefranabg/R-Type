#include				"Ennemy.hh"

Ennemy::Ennemy(int _id, EnnemyType _type) : APlayer(_id)
{
	this->sizeX = 65;
	this->sizeY = 67;
	this->isEnnemy = true;
	if (rand() % 2 == 0)
		this->direction = UP;
	else
		this->direction = DOWN;
	this->life = 1;
	this->type = _type;
}

Ennemy::~Ennemy()
{

}

bool					Ennemy::getBonus() const
{
	return (this->bonus);
}

void					Ennemy::play()
{
	return;
}

void					Ennemy::setDirection(e_action value)
{
	this->direction = value;
}

e_action					Ennemy::getDirection() const
{
	return (this->direction);
}

EnnemyType				Ennemy::getType() const
{
	return (this->type);
}

