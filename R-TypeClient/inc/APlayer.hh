#ifndef					APLAYER_HH_
# define				APLAYER_HH_

#include				"ProtocolOpcodes.hh"
#include				"Object.hh"
#include				<iostream>
#include				<mutex>
#include				<vector>


class					APlayer : public Object
{
protected:
	int					id;
	std::vector<e_action> actions;
	bool				isAlive;
	bool				isEnnemy;
	std::mutex			mutex;
	int					life;
public:
	APlayer(int id);
	~APlayer();
	int					getId() const;
	void				setNextAction(e_action);
	void				setIsAlive(bool);
	bool				getIsAlive() const;
	virtual void		play() = 0;
	bool				getIsEnnemy() const;
	void				resetPositions();
	void				clearActions();
	unsigned int		getActionListSize() const;
	e_action			getNextAction() const;
	void				delFirstAction();
	int					getLife() const;
	void				setLife(int);
};


#endif