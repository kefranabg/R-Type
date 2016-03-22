

#ifndef					ASOCKET_HH_
# define				ASOCKET_HH_

# include				"CString.hpp"
# include				<iostream>
# include				<stdexcept>
# include				<string>

# define				DEFAULT_PORT		"27015"
# define				DEFAULT_BUFFLEN		512
# define				DEFAULT_LISTEN		42

class					ASocket
{
protected:
  int					_socket;

public:
  ASocket();
  virtual				~ASocket();
  virtual int				socketInit(int, int, int) = 0;
  virtual int				socketBind() = 0;
  virtual int				socketListen() = 0;
  virtual int				socketAccept() = 0;
  virtual int				socketAccept(std::string &) = 0;
  virtual int				socketClientQuit(int) = 0;
  virtual int				socketQuit() = 0;
  int					getSocket() const;
};

#endif
