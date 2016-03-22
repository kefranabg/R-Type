//
// main.cpp for main.cpp in /home/abgral_f/dev/R-Type/R-TypeClient
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Sun Nov 16 16:51:13 2014 abgral_f
// Last update Thu Nov 20 11:43:03 2014 abgral_f
//

#include		"Client.hh"
#include		"Menus.h"

int			main()
{
  Client		c;

 
  /*c.Connection(27015, "192.168.1.18");
  if (c.getIsConnected() == false)
    return (-1);*/
  c.start();
  return (0);
}
