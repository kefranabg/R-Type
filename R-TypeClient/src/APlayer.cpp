#include			"APlayer.hh"

APlayer::APlayer(int _id)
{
	this->id = _id;
	this->isAlive = true;
	resetPositions();
}

APlayer::~APlayer()
{
		
}

void				APlayer::resetPositions()
{
	this->posX = -1;
	this->posY = -1;
	this->posOnCaseX = -1;
	this->posOnCaseY = -1;
}

int					APlayer::getId() const
{
	return (this->id);
}

void				APlayer::setNextAction(e_action action)
{
	this->mutex.lock();
	this->actions.push_back(action);
	this->mutex.unlock();
}

bool				APlayer::getIsAlive() const
{
	return (this->isAlive);
}

void				APlayer::setIsAlive(bool value)
{
	this->isAlive = value;
}

bool				APlayer::getIsEnnemy() const
{
	return (this->isEnnemy);
}

void				APlayer::clearActions()
{
	actions.clear();
}

e_action			APlayer::getNextAction() const
{
	return (this->actions[0]);
}

unsigned int		APlayer::getActionListSize() const
{
	return (this->actions.size());
}

void				APlayer::delFirstAction()
{
	this->mutex.lock();
	this->actions.front() = std::move(this->actions.back());
	this->actions.pop_back();

	this->mutex.unlock();
}

int					APlayer::getLife() const
{
	return (this->life);
}

void				APlayer::setLife(int life)
{
	this->life = life;
}