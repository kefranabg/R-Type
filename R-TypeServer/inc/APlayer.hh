#ifndef					APLAYER_HH_
# define				APLAYER_HH_

#include				<iostream>
#include				<vector>
#include				"Object.hh"
#include				"ProtocolOpcodes.hh"

class					APlayer : public Object
{
protected:
	int					id;
	int					life;
	std::vector<e_action> actions;
	bool				isAlive;
	bool				isEnnemy;
public:
	APlayer(int id);
	~APlayer();
	int					getId() const;
	void				setNextAction(e_action);
	void				setIsAlive(bool);
	bool				getIsAlive() const;
	virtual void		play() = 0;
	e_action			getNextAction() const;
	void				delFirstAction();
	void				clearActions();
	unsigned int		getActionListSize() const;
	bool				getIsEnnemy() const;
	int 				getLife() const;
	void				setLife(int);
};


#endif