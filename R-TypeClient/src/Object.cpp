#include			"Object.hh"

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