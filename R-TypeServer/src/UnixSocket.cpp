//
// UnixSocket.cpp for UnixSocket.cpp in /home/loeb_t/test
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Thu Oct  9 13:20:10 2014 LOEB Thomas
// Last update Sun Nov 16 16:44:10 2014 abgral_f
//

#include		<sstream>
#include		<unistd.h>
#include		"UnixSocket.hh"

UnixSocket::UnixSocket() {}

UnixSocket::~UnixSocket() {}

int			UnixSocket::socketInit(int domain, int type, int protocol) {
  if ((_socket = socket(domain, type, protocol)) == -1)
    std::cerr << ERROR_FCT("socket")":" << CString::getError() << std::endl;
  return (_socket);
}

int			UnixSocket::socketBind() {
  struct sockaddr_in	server;
  std::istringstream    iss(DEFAULT_PORT);
  int                   port;

  iss >> port;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;
  if (bind(_socket, (const struct sockaddr *)(&server), sizeof(server)) == -1) {
	  std::cerr << ERROR_FCT("bind")":" << CString::getError() << std::endl;
	  return (-1);
  }
  return (0);
}

int			UnixSocket::socketListen() {
  if (listen(_socket, SOMAXCONN) == -1) {
    std::cerr << ERROR_FCT("listen")":" << CString::getError() << std::endl;
    return (-1);
  }
  return (0);
}

int			UnixSocket::socketAccept() {
  int		ret = accept(_socket, NULL, NULL);

  if (ret == -1) {
    std::cerr << ERROR_FCT("accept")":" << CString::getError() << std::endl;
    return (-1);
  }
  return (ret);
}

int			UnixSocket::socketAccept(std::string &ip_client) {
  struct sockaddr_in	client;
  socklen_t		size_client;
  int			ret;

  size_client = sizeof(struct sockaddr_in);
  if ((ret = accept(_socket, (struct sockaddr *)(&client), &size_client)) == -1) {
	  std::cerr << ERROR_FCT("accept")":" << CString::getError() << std::endl;
	  ip_client = "";
	  return (-1);
  }
  ip_client = inet_ntoa(client.sin_addr);
  return (ret);
}

int			UnixSocket::socketQuit() {
  if (_socket != -1)
	  if (close(_socket) == -1) {
	  std::cerr << ERROR_FCT("close")":" << CString::getError() << std::endl;
	  return (-1);
	  }
  return (0);
}

int			UnixSocket::socketClientQuit(int clientSocket) {
	if (shutdown(clientSocket, SHUT_RD) == -1) {
		std::cerr << ERROR_FCT("shutdown")":" << CString::getError() << std::endl;
		if (close(clientSocket) == -1)
			std::cerr << ERROR_FCT("close")":" << CString::getError() << std::endl;
		return (-1);
	}
	if (close(clientSocket) == -1) {
		std::cerr << ERROR_FCT("close")":" << CString::getError() << std::endl;
		return (-1);
	}
	return (0);
}
