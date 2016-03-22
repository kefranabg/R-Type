#include			"Object.hh"
#include <iostream>

Object::Object()
{

}

Object::~Object()
{

}

int					Object::getPosX() const
{
	return (this->posX);
}

int					Object::getPosY() const
{
	return (this->posY);
}

int					Object::getPosOnCaseX() const
{
	return (this->posOnCaseX);
}
int					Object::getPosOnCaseY() const
{
	return(this->posOnCaseY);
}

int					Object::getSizeX() const
{
	return (this->sizeX);
}

int					Object::getSizeY() const
{
	return (this->sizeY);
}

void				Object::setPosX(int value)
{
	this->posX = value;
}

void				Object::setPosY(int value)
{
	this->posY = value;
}

void				Object::setPosOnCaseX(int value)
{
	this->posOnCaseX = value;
	if (this->posOnCaseX >= 10)
	{
		this->posOnCaseX = 0;
		this->posX += 1;
	}
	else if (this->posOnCaseX <= -1)
	{
		this->posOnCaseX = 9;
		this->posX -= 1;
	}
}

void				Object::setPosOnCaseY(int value)
{
	this->posOnCaseY = value;
	if (this->posOnCaseY >= 10)
	{
		this->posOnCaseY = 0;
		this->posY += 1;
	}
	else if (this->posOnCaseY <= -1)
	{
		this->posOnCaseY = 9;
		this->posY -= 1;
	}
}

void				Object::setSizeX(int value)
{
	this->sizeX = value;
}

void				Object::setSizeY(int value)
{
	this->sizeY = value;
}

bool				Object::checkCollision(const Object *obj) const
{
	int playerX1, playerX2, playerY1, playerY2;
	int objX1, objX2, objY1, objY2;

	playerX1 = (this->getPosX() * 100 + this->getPosOnCaseX() * 10) - this->getSizeX() / 2;
	playerX2 = (this->getPosX() * 100 + this->getPosOnCaseX() * 10) + this->getSizeX() / 2;
	playerY1 = (this->getPosY() * 100 + this->getPosOnCaseY() * 10) - this->getSizeY() / 2;
	playerY2 = (this->getPosY() * 100 + this->getPosOnCaseY() * 10) + this->getSizeY() / 2;
	objX1 = (obj->getPosX() * 100 + obj->getPosOnCaseX() * 10) - obj->getSizeX() / 2;
	objX2 = (obj->getPosX() * 100 + obj->getPosOnCaseX() * 10) + obj->getSizeX() / 2;
	objY1 = (obj->getPosY() * 100 + obj->getPosOnCaseY() * 10) - obj->getSizeY() / 2;
	objY2 = (obj->getPosY() * 100 + obj->getPosOnCaseY() * 10) + obj->getSizeY() / 2;

	if (((objX1 > playerX1 && objX1 < playerX2) &&
		(objY1 > playerY1 && objY1 < playerY2)) ||
		((objX2 > playerX1 && objX2 < playerX2) &&
		(objY2 > playerY1 && objY2 < playerY2)))
		return true;
	return false;
}