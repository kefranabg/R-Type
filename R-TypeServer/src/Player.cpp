#include					"Player.hh"

Player::Player(ClientInfo *_infos, int _id) : APlayer(_id)
{
	this->infos = _infos;
	this->sizeX = 53;
	this->sizeY = 30;
	this->isEnnemy = false;
	this->life = 3;
}

Player::~Player()
{

}

ClientInfo				*Player::getClientInfo()
{
	return (this->infos);
}

void					Player::play()
{
	return ;
}