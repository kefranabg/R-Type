#ifndef		UNIXDLIBRARY_HH__
#define		UNIXDLIBRARY_HH__

#ifndef		_WIN32

#include	<dlfcn.h>
#include	"ADLibrary.hh"

class		UnixDLibrary : public ADLibrary
{
public:
  UnixDLibrary();
  ~UnixDLibrary();

public:
  void		*open(const char *name);
  void		*symbol(void *lib, const char *sym);
  int		close(void *lib);

private:
};

#endif		// _WIN32

#endif		// UNIXDLIBRARY_HH__
