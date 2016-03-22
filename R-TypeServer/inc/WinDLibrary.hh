#ifndef		WINDLIBRARY_HH__
#define		WINDLIBRARY_HH__

#ifdef		_WIN32

#include	<windows.h>
#include	"ADLibrary.hh"

class		WinDLibrary : public ADLibrary
{
public:
  WinDLibrary();
  ~WinDLibrary();

public:
  void		*open(const char *name);
  void		*symbol(void *lib, const char *sym);
  int		close(void *lib);

private:
};

#endif		// _WIN32

#endif		// WINDLIBRARY_HH__
