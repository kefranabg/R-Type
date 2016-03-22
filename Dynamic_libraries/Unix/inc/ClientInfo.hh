//
// ClientInfos.hh for ClientInfos.hh in /home/abgral_f/dev/R-Type/R-TypeServer
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Sun Nov 16 21:43:04 2014 abgral_f
// Last update Mon Nov 17 22:35:26 2014 abgral_f
//

#ifndef				CLIENTINFO_HH_
# define			CLIENTINFO_HH_

#include			<iostream>
#include			<stdio.h>
#include			<string.h>
#ifndef				WIN32
#include			<netinet/in.h>
#else
#include			<winsock2.h>
#endif

class				ClientInfo
{
private:
  struct sockaddr_in		*addr;
  int				roomId;
  std::string			name;
  bool				isReady;
  bool				isReadyToGame;
  int				id;
public:
  ClientInfo(int, struct sockaddr_in *);
  ~ClientInfo();
  int				getRoomId() const;
  struct sockaddr_in		*getAddr();
  const std::string		&getName() const;
  int				getId() const;
  bool				getIsReady() const;
  bool				getIsReadyToGame() const;
  void				setRoomId(int);
  void				setAddr(struct sockaddr_in *);
  void				setName(std::string &);
  void				setIsReady(bool);
  void				setIsReadyToGame(bool);
  void				setId(int);
};

#endif
