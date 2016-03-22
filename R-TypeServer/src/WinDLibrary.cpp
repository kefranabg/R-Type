#ifdef		_WIN32

#include	"WinDLibrary.hh"

WinDLibrary::WinDLibrary()
{
}

WinDLibrary::~WinDLibrary()
{
}

void		*WinDLibrary::open(const char *name)
{
  return (LoadLibrary((LPCSTR)name));
}

void		*WinDLibrary::symbol(void *lib, const char *sym)
{
  return ((void *)GetProcAddress((HMODULE)lib, (LPCSTR)sym));
}

int		WinDLibrary::close(void *lib)
{
  return ((int)FreeLibrary((HMODULE)lib);
}

#endif		// _WIN32
