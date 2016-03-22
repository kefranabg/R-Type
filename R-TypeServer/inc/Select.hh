
#ifndef				SELECT_HH_
# define			SELECT_HH_

# ifdef				_WIN32
#  include			"stdafx.h"
# else
#  include			<sys/select.h>
#  include			<sys/time.h>
#  include			<sys/types.h>
#  include			<unistd.h>
# endif
# include			<string>

class				Select
{
private:
  int				_nfds;
  fd_set			_readFds;
  fd_set			_writeFds;
  fd_set			_exceptFds;

public:
  Select();
  ~Select();
  void				fdsZero(const std::string &);
  void				fdsSet(const std::string &, int);
  void				fdsRemove(const std::string &, int);
  int				doSelect(struct timeval *);
  bool				isFdSet(char, int);
};

#endif
