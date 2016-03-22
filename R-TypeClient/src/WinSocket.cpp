
#include				"WinSocket.hh"

WinSocket::WinSocket() : ASocket()
{
}


WinSocket::~WinSocket()
{
}

int						WinSocket::socketInit(int domain, int type, int protocol)
{
  int						ret;
  WSADATA					wsaData;
  std::istringstream			    buffer(DEFAULT_PORT);
  int						port;

  buffer >> port;
  if ((ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
    std::cerr << ERROR_FCT("WSAStartup")":" << CString::getError(ret) << std::endl;
    return (-1);
  }
  if ((_socket = socket(domain, type, protocol)) == INVALID_SOCKET) {
	  std::cerr << ERROR_FCT("socket")":" << CString::getErrorNetwork() << std::endl;
	  return (-1);
  }
  addr.sin_family = domain;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  return (0);
}

int						WinSocket::socketBind()
{
  struct addrinfo			*ptr = NULL;

  if (bind(_socket, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
	  std::cerr << ERROR_FCT("bind")":" << CString::getErrorNetwork() << std::endl;
	return (-1);
  }
  return (0);
}

int						WinSocket::socketListen()
{
	if (listen(_socket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << ERROR_FCT("listen")":" << CString::getErrorNetwork() << std::endl;
		return (-1);
	}
	return (0);
}

int						WinSocket::socketAccept()
{
	int					ret = accept(_socket, NULL, NULL);

	if (ret == INVALID_SOCKET) {
		std::cerr << ERROR_FCT("accept")":" << CString::getErrorNetwork() << std::endl;
		return (-1);
	}
	return (ret);
}

int						WinSocket::socketAccept(std::string &ip_client)
{
  struct sockaddr_in    client;
  socklen_t             size_client;
  int                   ret;

  size_client = sizeof(struct sockaddr_in);
  if ((ret = accept(_socket, (struct sockaddr *)(&client), &size_client)) == INVALID_SOCKET) {
	  std::cerr << ERROR_FCT("accept")":" << CString::getErrorNetwork() << std::endl;
	  ip_client = "";
	  return (-1);
  }
  ip_client = inet_ntoa(client.sin_addr);
  return (ret);
}

int						WinSocket::socketQuit()
{
  if (_socket != -1)
    if (closesocket(_socket) == SOCKET_ERROR) {
      std::cerr << ERROR_FCT("closesocket")":" << CString::getErrorNetwork() << std::endl;
      if (WSACleanup() == SOCKET_ERROR)
		  std::cerr << ERROR_FCT("WSACleanup")":" << CString::getErrorNetwork() << std::endl;
      return (-1);
    }
  if (WSACleanup() == SOCKET_ERROR) {
	  std::cerr << ERROR_FCT("WSACleanup")":" << CString::getErrorNetwork() << std::endl;
	  return (-1);
  }
  return (0);
}

int						WinSocket::socketClientQuit(int clientSocket)
{
  if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {
	  std::cerr << ERROR_FCT("shutdown")":" << CString::getErrorNetwork() << std::endl;
	  if (closesocket(clientSocket) == SOCKET_ERROR)
		std::cerr << ERROR_FCT("closesocket")":" << CString::getErrorNetwork() << std::endl;
    return (-1);
  }
  if (closesocket(clientSocket) == SOCKET_ERROR) {
	  std::cerr << ERROR_FCT("closesocket")":" << CString::getErrorNetwork() << std::endl;
    return (-1);
  }
  return (0);
}
