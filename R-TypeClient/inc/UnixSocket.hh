
#ifndef				UNIXSOCKET_HH_
# define			UNIXSOCKET_HH_

# include			<sys/types.h>
# include			<sys/socket.h>
# include			<netinet/in.h>
# include			<arpa/inet.h>
# include			"ASocket.hh"

class				UnixSocket : public ASocket {
public:
  UnixSocket();
  virtual			~UnixSocket();
  virtual int			socketInit(int, int, int);
  virtual int			socketBind();
  virtual int			socketListen();
  virtual int			socketAccept();
  virtual int			socketAccept(std::string &);
  virtual int			socketQuit();
  virtual int			socketClientQuit(int);
};

#endif				/* UNIXSOCKET_HH_ */
