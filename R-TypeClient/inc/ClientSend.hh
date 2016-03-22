//
// ClientSend.hh for ClientSend.hh in /home/abgral_f/dev/R-Type/R-TypeServer
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Nov 17 14:30:26 2014 abgral_f
// Last update Wed Nov 19 19:00:07 2014 abgral_f
//

#ifndef				CLIENTSEND_HH_
# define			CLIENTSEND_HH_

#include                        "ProtocolOpcodes.hh"
#include                        <vector>
#include                        <string.h>
#include			<iostream>

class				ClientSend
{
public:
  ClientSend();
  ~ClientSend();
  std::vector<char>	*createData(ClientOpcodes, int, void *) const;
  std::vector<char>	*connectSnd() const;
  std::vector<char>	*chooseNameSnd(const std::string &) const;
  std::vector<char>	*createPoolSnd(const std::string &) const;
  std::vector<char>	*choosenMapSnd(const std::string &) const;
  std::vector<char>	*listPlayerSnd() const;
  std::vector<char>	*listPoolSnd() const;
  std::vector<char>	*joinPoolSnd(const std::string &) const;
  std::vector<char>	*statusSnd(bool) const;
  std::vector<char>	*quitPoolSnd() const;
  std::vector<char>	*playerActionSnd(e_action) const;
  std::vector<char>	*playerDieSnd() const;
  std::vector<char>	*readyToGameSnd() const;
  std::vector<char>	*playerFinishSnd() const;
  std::vector<char>	*listMapSnd() const;
  std::vector<char>	*disconnectSnd() const;
};

#endif
