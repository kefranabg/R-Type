#ifndef		IDLIBRARY_H__
#define		IDLIBRARY_H__

class		IDLibrary
{
public:
  virtual void	*open(const char *name) = 0;
  virtual void	*symbol(void *lib, const char *sym) = 0;
  virtual int	close(void *lib) = 0;

private:

};

#endif		/* IDLIBRARY_H__ */
