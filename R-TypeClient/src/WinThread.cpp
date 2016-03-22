

#include			"WinThread.hh"

WinThread::WinThread()
{
}

WinThread::~WinThread()
{
}

int				WinThread::threadCreate(threadFunction func, void *param)
{
	if ((_thread = CreateThread(NULL, 0, func, param, 0, NULL)) == NULL) {
		std::cerr << ERROR_FCT("CreateThread")":" << CString::getError() << std::endl;
		return (-1);
	}
  return (0);
}

int				WinThread::threadWait()
{
	DWORD		wfso = WaitForSingleObject(_thread, INFINITE);

	if (wfso == WAIT_FAILED) {
		std::cerr << ERROR_FCT("WaitForSingleObject")":" << CString::getError() << std::endl;
		return (-1);
	}
  return (wfso);
}

int				WinThread::threadQuit(int retVal)
{
  ExitThread(retVal);
  return (0);
}

int				WinThread::threadKill(int retVal)
{
	BOOL		tt = TerminateThread(_thread, retVal);

	if (tt == 0) {
		std::cerr << ERROR_FCT("TerminateThread")":" << CString::getError() << std::endl;
		return (-1);
	}
  return (tt);
}
