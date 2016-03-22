
#ifndef				CSTRING_HPP_
# define			CSTRING_HPP_


# include			<cerrno>
# include			<cstring>
# ifdef				_WIN32
#  include			"stdafx.h"
# else
# include			<iostream>
# endif

# define			ERROR_MSG		"[ERROR]"
# define			ERROR_FCT(x)		ERROR_MSG ":[" x "]"
# define			SUCCESS_MSG		"[SUCCESS]"
# define			SUCCESS_FCT(x)		SUCCESS_MSG ":[" x "]"

# define			CLIENT_STR		"Client "

# define			CLIENT_WAITED		CLIENT_STR "added, waiting for authentication"
# define			CLIENT_DELETED		CLIENT_STR "deleted"
# define			CLIENT_AUTHENTICATED	CLIENT_STR "authenticated"
# define			CLIENT_DISCONNECTED	CLIENT_STR "disconnected"

# define			UNAUTH_STR		"Unauthenticated "

# define			UNCLIENT_DELETED	UNAUTH_STR CLIENT_DELETED

class				CString {
public:
  static void			setMemory(void *p, int b, size_t n) {
    memset(p, b, n);
  }

  static void			copyMemory(void *d, const void *s, size_t n) {
    memcpy(d, s, n);
  }

  static const std::string	getError() {
# ifdef				_WIN32
    char *tmp = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		  FORMAT_MESSAGE_FROM_SYSTEM |
		  FORMAT_MESSAGE_IGNORE_INSERTS,
		  NULL,
		  GetLastError(),
		  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		  reinterpret_cast<LPTSTR>(&tmp),
		  0, NULL);

    std::string error(tmp);
    LocalFree(tmp);
# else
    std::string			error(strerror(errno));
# endif
    return (error);
  }

  static const std::string	getError(int value) {
# ifdef				_WIN32
    char *tmp = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		  FORMAT_MESSAGE_FROM_SYSTEM |
		  FORMAT_MESSAGE_IGNORE_INSERTS,
		  NULL,
		  value,
		  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		  reinterpret_cast<LPTSTR>(&tmp),
		  0, NULL);

    std::string error(tmp);
    LocalFree(tmp);
# else
    std::string			error(strerror(value));
# endif
    return (error);
  }

# ifdef				_WIN32
  static const std::string	getErrorNetwork() {
    char *tmp = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		  FORMAT_MESSAGE_FROM_SYSTEM |
		  FORMAT_MESSAGE_IGNORE_INSERTS,
		  NULL,
		  WSAGetLastError(),
		  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		  reinterpret_cast<LPTSTR>(&tmp),
		  0, NULL);

    std::string error(tmp);
    LocalFree(tmp);
    return (error);
  }
# endif
};

#endif
