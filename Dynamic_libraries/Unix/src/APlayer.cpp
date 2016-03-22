#include			"APlayer.hh"

APlayer::APlayer(int _id)
{
	this->id = _id;
	this->isAlive = true;
}

APlayer::~APlayer()
{

}

int					APlayer::getId() const
{
	return (this->id);
}

void				APlayer::setNextAction(e_action action)
{
	this->actions.push_back(action);
}

bool				APlayer::getIsAlive() const
{
	return (this->isAlive);
}

void				APlayer::setIsAlive(bool value)
{
	this->isAlive = value;
}

void				APlayer::clearActions()
{
	actions.clear();
}

e_action			APlayer:: getNextAction() const
{
	return (this->actions[0]);
}

unsigned int		APlayer::getActionListSize() const
{
	return (this->actions.size());
}

void				APlayer::delFirstAction()
{
	this->actions.front() = std::move(this->actions.back());
	this->actions.pop_back();
}

bool				APlayer::getIsEnnemy() const
{
	return (this->isEnnemy);
}

int 				APlayer::getLife() const
{
	return (this->life);
}

void				APlayer::setLife(int life)
{
	this->life = life;
}