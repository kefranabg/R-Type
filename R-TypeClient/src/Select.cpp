
#include		"Select.hh"
#include		"ASocket.hh"

Select::Select()
{
  this->_nfds = 3;
  FD_ZERO(&(this->_readFds));
  FD_ZERO(&(this->_writeFds));
  FD_ZERO(&(this->_exceptFds));
}

Select::~Select() {}

void			Select::fdsZero(const std::string &list)
{
  for (unsigned int i = 0; i < list.length(); ++i)
    if (list[i] == 'r')
      FD_ZERO(&(this->_readFds));
    else if (list[i] == 'w')
      FD_ZERO(&(this->_writeFds));
    else if (list[i] == 'e')
      FD_ZERO(&(this->_exceptFds));
}

void			Select::fdsSet(const std::string &list, int fd)
{
  for (unsigned int i = 0; i < list.length(); ++i)
    {
      if (list[i] == 'r')
	FD_SET(fd, &(this->_readFds));
      else if (list[i] == 'w')
	FD_SET(fd, &(this->_writeFds));
      else if (list[i] == 'e')
	FD_SET(fd, &(this->_exceptFds));
      if (fd >= this->_nfds)
	this->_nfds = fd + 1;
    }
}

void			Select::fdsRemove(const std::string &list, int fd)
{
  for (unsigned int i = 0; i < list.length(); ++i)
    {
      if (list[i] == 'r')
	FD_CLR(fd, &(this->_readFds));
      else if (list[i] == 'w')
	FD_CLR(fd, &(this->_writeFds));
      else if (list[i] == 'e')
	FD_CLR(fd, &(this->_exceptFds));
    }
}

int				Select::doSelect(struct timeval *selectTime)
{
  int			ret = select(this->_nfds, &(this->_readFds), &(this->_writeFds), &(this->_exceptFds), selectTime);

#ifdef _WIN32
  if (ret == SOCKET_ERROR) {
    std::cerr << ERROR_FCT("select")":" << CString::getErrorNetwork() << std::endl;
#else
    if (ret == -1) {
      std::cerr << ERROR_FCT("select")":" << CString::getError() << std::endl;
#endif
      return (-1);
    }
    return (ret);
  }

bool			Select::isFdSet(char fdList, int fd)
{
  bool		ret = false;

  if (fdList == 'r')
    ret = (FD_ISSET(fd, &(this->_readFds))) ? true : false;
  if (fdList == 'w')
    ret = (FD_ISSET(fd, &(this->_writeFds))) ? true : false;
  if (fdList == 'e')
    ret = (FD_ISSET(fd, &(this->_exceptFds))) ? true : false;
  return (ret);
}
