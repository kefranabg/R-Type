
#ifndef				WINTHREAD_HH_
# define			WINTHREAD_HH_

# include			"IThread.hh"

class				WinThread : public IThread
{
private:
  HANDLE			_thread;

public:
  WinThread();
  virtual			~WinThread();
  virtual int			threadCreate(threadFunction, void *);
  virtual int			threadWait();
  virtual int			threadQuit(int);
  virtual int			threadKill(int);
};

#endif
