
#ifndef			ITHREAD_HH_
# define		ITHREAD_HH_

# ifdef			_WIN32
# include		"stdafx.h"
typedef LPTHREAD_START_ROUTINE threadFunction;
# else
typedef void		*(*threadFunction)(void *);
# endif
# include		"ASocket.hh"
# include		<iostream>
# include		<string>

class IThread
{
public:
  IThread() {}
  virtual			~IThread() {}
  virtual int		threadCreate(threadFunction, void *) = 0;
  virtual int		threadWait() = 0;
  virtual int		threadQuit(int) = 0;
  virtual int		threadKill(int) = 0;
};

#endif
