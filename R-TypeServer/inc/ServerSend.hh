//
// ServerSend.hh for ServerSend.hh in /home/abgral_f/dev/R-Type/R-TypeServer
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Nov 17 13:39:41 2014 abgral_f
// Last update Thu Nov 20 18:29:30 2014 abgral_f
//

#ifndef				SERVERSEND_HH_
# define			SERVERSEND_HH_

#include			<vector>
#include			<string.h>
#include			<iostream>
#include			"ProtocolOpcodes.hh"
#include			"Ennemy.hh"

class				ServerSend
{
public:
  ServerSend();
  ~ServerSend();
  std::vector<char>		*createData(ServerOpcodes, int, void *) const;
  std::vector<char>             *connectSnd(bool, int) const;
  std::vector<char>		*disconnectSnd() const;
  std::vector<char>		*chooseNameSnd(bool) const;
  std::vector<char>		*createPoolSnd(bool, const std::string &) const;
  std::vector<char>		*listPoolSnd(const std::string &) const;
  std::vector<char>	        *playerJoinPoolSnd(const std::string &, int) const;
  std::vector<char>		*joinPoolSnd(e_JoinPoolResponse, const std::string &) const;
  std::vector<char>		*playerStatusSnd(bool, int, const std::string &) const;
  std::vector<char>		*playerQuitSnd(int, const std::string &) const;
  std::vector<char>		*launchGameSnd() const;
  std::vector<char>		*playerPosSnd(int, int, int, int, int) const;
  std::vector<char>		*playerActionSnd(int, e_action) const;
  std::vector<char>		*playerDieSnd(int) const;
  std::vector<char>		*newEnnemySnd(int, int, int, int, int, EnnemyType) const;
  std::vector<char>		*endGameSnd(bool) const;
  std::vector<char>		*dataMapSnd(std::vector<std::vector<char>> *) const;
  std::vector<char>		*missileExploseSnd(int) const;
  std::vector<char>		*ennemyDieSnd(int) const;
  std::vector<char>		*listMapSnd(const std::string &) const;
  std::vector<char>		*ennemyActionSnd(int, e_action) const;
  std::vector<char>		*newMissileSnd(int, int, bool, int, int, int, int, e_action) const;
  std::vector<char>		*nextFrameSnd() const;
  std::vector<char>		*playerLifeSnd(int) const;
  std::vector<char>		*newBonusSnd(Type, int, int, int, int, int) const;
  std::vector<char>		*deleteBonusSnd(int) const;
};

#endif
