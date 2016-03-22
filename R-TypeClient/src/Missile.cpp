#include				"Missile.hh"

Missile::Missile(int _id, int _idPlayer, bool _isEnnemy, int _posX,
					int _posY, int _posOnCaseX, int _posOnCaseY, e_action _direction)
{
	this->id = _id;
	this->idPlayer = _idPlayer;
	this->isEnnemy = _isEnnemy;
	this->posX = _posX;
	this->posY = _posY;
	this->posOnCaseX = _posOnCaseX;
	this->posOnCaseY = _posOnCaseY;
	this->direction = _direction;
	this->sizeX = 55;
	this->sizeY = 23;
}

Missile::~Missile()
{
	
}

bool				Missile::getIsEnnemy() const
{
	return (this->isEnnemy);
}

e_action			Missile::getDirection() const
{
	return (this->direction);
}

int					Missile::getIdPlayer() const
{
	return (this->idPlayer);
}

int					Missile::getId() const
{
	return (this->id);
}