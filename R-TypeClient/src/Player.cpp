#include					"Player.hh"

Player::Player(int _id) : APlayer(_id)
{
	this->isReady = false;
	this->sizeX = 53;
	this->sizeY = 30;
	this->isEnnemy = false;
	this->life = 3;
}

Player::~Player()
{

}

void					Player::play()
{
	return ;
}

void					Player::setIsReady(bool value)
{
	this->isReady = value;
}

bool					Player::getIsReady() const
{
	return (this->isReady);
}