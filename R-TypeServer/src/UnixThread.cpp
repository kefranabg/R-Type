//
// UnixThread.cpp for UnixThread.cpp in /home/loeb_t/test
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Fri Oct 10 13:31:36 2014 LOEB Thomas
// Last update Fri Oct 10 13:42:03 2014 LOEB Thomas
//

#include	"UnixThread.hh"

UnixThread::UnixThread() {}

UnixThread::~UnixThread() {}

int		UnixThread::threadCreate(threadFunction startRoutine, void *arg) {
	if ((errno = pthread_create(&_thread, NULL, startRoutine, arg)) != 0) {
		std::cerr << ERROR_FCT("pthread_create")":" << CString::getError() << std::endl;
		return (-1);
	}
	return (0);
}

int		UnixThread::threadWait() {
	if ((errno = pthread_join(_thread, NULL)) != 0) {
		std::cerr << ERROR_FCT("pthread_join")":" << CString::getError() << std::endl;
		return (-1);
	}
	return (0);
}

int		UnixThread::threadQuit(int ret) {
  pthread_exit(&ret);
  return (0);
}

int		UnixThread::threadKill(int ret __attribute__((__unused__))) {
	if ((errno = pthread_cancel(_thread)) != 0) {
		std::cerr << ERROR_FCT("pthread_cancel")":" << CString::getError() << std::endl;
		return (-1);
	}
	return (0);
}
