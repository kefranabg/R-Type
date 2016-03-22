#ifndef						PLAYER_HH_
# define					PLAYER_HH_

#include					"APlayer.hh"

class						Player : public APlayer
{
private:
	bool					isReady;
public:
	Player(int);
	~Player();
	virtual void			play();
	bool					getIsReady() const;
	void					setIsReady(bool);
};

#endif