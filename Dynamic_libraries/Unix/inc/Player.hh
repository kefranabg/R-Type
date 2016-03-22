#ifndef						PLAYER_HH_
# define					PLAYER_HH_

#include					"APlayer.hh"
#include					"ClientInfo.hh"

class						Player : public APlayer
{
private:
	ClientInfo				*infos;
public:
	Player(ClientInfo *, int);
	~Player();
	virtual void			play();
	ClientInfo				*getClientInfo();
};

#endif