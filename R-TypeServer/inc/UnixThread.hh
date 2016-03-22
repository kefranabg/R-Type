
#ifndef			UNIXTHREAD_HH_
# define		UNIXTHREAD_HH_

# include		<pthread.h>
# include		"IThread.hh"

class			UnixThread : public IThread {
private:
  pthread_t		_thread;

public:
  UnixThread();
  virtual		~UnixThread();
  virtual int		threadCreate(threadFunction, void *);
  virtual int		threadWait();
  virtual int		threadQuit(int);
  virtual int		threadKill(int);
};

#endif			/* UNIXTHREAD_HH_ */
