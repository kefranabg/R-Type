#include				"Ennemy.hh"

Ennemy::Ennemy(int _id, EnnemyType _type) : APlayer(_id)
{
	this->sizeX = 65;
	this->sizeY = 67;
	this->isEnnemy = true;
	this->type = _type;
	this->anim = 0;
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

EnnemyType				Ennemy::getType() const
{
	return (this->type);
}

int						Ennemy::getAnim() const
{
	return this->anim;
}

void					Ennemy::changeAnim()
{
	this->anim = (this->anim + 1) % 5;
}