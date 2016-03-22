//
// ClientInfos.cpp for ClientInfos.cpp in /home/abgral_f/dev/R-Type/R-TypeServer
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Sun Nov 16 21:54:50 2014 abgral_f
// Last update Sun Nov 23 10:08:53 2014 abgral_f
//

#include			"ClientInfo.hh"

ClientInfo::ClientInfo(int _id, struct sockaddr_in *_addr)
{
  this->id = _id;
  this->addr = new struct sockaddr_in();
  memcpy(this->addr, _addr, sizeof(struct sockaddr_in));
  this->name = "";
  this->isReady = false;
  this->isReadyToGame = false;
  this->roomId = -1;
}

ClientInfo::~ClientInfo()
{

}

int				ClientInfo::getRoomId() const
{
  return (roomId);
}

struct sockaddr_in		*ClientInfo::getAddr()
{
  return (addr);
}

const std::string		&ClientInfo::getName() const
{
  return (name);
}

int				ClientInfo::getId() const
{
  return (id);
}

bool				ClientInfo::getIsReady() const
{
  return (isReady);
}

bool				ClientInfo::getIsReadyToGame() const
{
	return (isReadyToGame);
}

void                          ClientInfo::setRoomId(int _roomId)
{
  this->roomId = _roomId;
}

void                          ClientInfo::setAddr(struct sockaddr_in *_addr)
{
  this->addr = _addr;
}

void                          ClientInfo::setName(std::string &name)
{
  this->name = name;
}

void                          ClientInfo::setIsReady(bool isReady)
{
  this->isReady = isReady;
}

void                          ClientInfo::setIsReadyToGame(bool isReady)
{
	this->isReadyToGame = isReady;
}

void                          ClientInfo::setId(int id)
{
  this->id = id;
}
