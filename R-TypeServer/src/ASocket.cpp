//
// ASocket.cpp for ASocket.cpp in /home/loeb_t/test
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Thu Oct 16 09:31:38 2014 LOEB Thomas
// Last update Thu Oct 16 17:50:41 2014 LOEB Thomas
//

#ifdef				_WIN32
# include			"stdafx.h"
#endif
#include			"ASocket.hh"

ASocket::ASocket()
{
  _socket = -1;
}

ASocket::~ASocket() {}

int				ASocket::getSocket() const
{
  return (_socket);
}
