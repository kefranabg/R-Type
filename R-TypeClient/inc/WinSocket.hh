
#ifndef				WINSOCKET_HH_
# define			WINSOCKET_HH_

# include			"ASocket.hh"
#include			<winsock2.h>
#include			<ws2tcpip.h>
#include			<stdio.h>
#include			<sstream>
#include			<string>

class				WinSocket : public ASocket
{
private:
	struct sockaddr_in	addr;

public:
  WinSocket();
  virtual			~WinSocket();
  virtual int			socketInit(int, int, int);
  virtual int			socketBind();
  virtual int			socketListen();
  virtual int			socketAccept();
  virtual int			socketAccept(std::string &);
  virtual int			socketClientQuit(int);
  virtual int			socketQuit();
};

#endif
