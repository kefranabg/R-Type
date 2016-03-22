#ifndef		_WIN32

#include	"UnixDLibrary.hh"

UnixDLibrary::UnixDLibrary()
{
}

UnixDLibrary::~UnixDLibrary()
{
}

void		*UnixDLibrary::open(const char *name)
{
  return (dlopen(name, RTLD_LAZY));
}

void		*UnixDLibrary::symbol(void *lib, const char *sym)
{
  return (dlsym(lib, sym));
}

int		UnixDLibrary::close(void *lib)
{
  return (dlclose(lib));
}

#endif		// _WIN32
