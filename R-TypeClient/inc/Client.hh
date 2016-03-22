//
// Client.hh for Client.hh in /home/abgral_f/dev/R-Type/R-TypeClient
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Sun Nov 16 17:12:16 2014 abgral_f
// Last update Thu Nov 20 20:54:03 2014 abgral_f
//

#ifndef                         CLIENT_HH_
# define                        CLIENT_HH_

#ifdef				WIN32
#include						"stdafx.h"
#include                        "WinSocket.hh"
#include                        "WinThread.hh"
#else
#include						<unistd.h>
#include                        "UnixSocket.hh"
#include                        "UnixThread.hh"
#endif

#include			"Select.hh"
#include			"ClientSend.hh"
#include			"Music.h"
#include			<vector>
#include			<thread>
#include			<SFML/Graphics.hpp>

/* ERRORS */

# define SOCKET_INIT_ERROR	"Socket init error"
# define WRITE_SOCKET_ERROR     "Error on sendto"
# define READ_SOCKET_ERROR      "Error on recvfrom"
# define WRONG_PACKET           "Wrong packet"
# define CONNECTION_ERROR	"Connection to Sever failed"

# define CONNECTED		"Connected"

# define SIZE_MAX_PACKET        4096
# define TV_USEC                500000

# define NB_OPCODES             25
# define WIN_MSG_DONTWAIT	2
# define CONNECTION_WAIT	5

class				Game;
class				Gui;
class				Menus;

class				Client
{
private:
  int				id;
  Select			select;
  bool				isConnected;
  ASocket                       *socket;
  struct timeval                tv;
  struct sockaddr_in		addr;
  ClientSend			doPacket;
  Game					*pool;
  Gui					*gui;
  std::thread			*launchGui;
  Menus					*menu;
  Music					*music;
  bool					exit;
public:
  Client();
  ~Client();
  bool				Connection(int, const std::string &);
  void				initSelect();
  void				start();
  void				setExit(bool);
  bool				getIsConnected() const;
  const std::vector<char>	*connectRequest();
  void				sendPacket(const std::vector<char> *) const;
  std::vector<char>             *getMsg(int);
  ServerOpcodes                 getOpcode(const std::vector<char> *) const;
  void				processPacketReception();
  const ClientSend  &getDoPacket() const;
  Game				*getGame() const;
  Music				*getMusic() const;
  void				quitMenuThread();
  void				launchGameGui(sf::RenderWindow *);
  void				launchMenu();

  /* Handle packets recieved */
  void				connectRecv(std::vector<char> *);
  void                          disconnectRecv(std::vector<char> *);
  void				chooseNameRecv(std::vector<char> *);
  void				createPoolRecv(std::vector<char> *);
  void				listPoolRecv(std::vector<char> *);
  void				dataMapRecv(std::vector<char> *);
  void				playerJoinPoolRecv(std::vector<char> *);
  void				joinPoolRespRecv(std::vector<char> *);
  void				playerStatusRecv(std::vector<char> *);
  void				playerQuitRecv(std::vector<char> *);
  void				launchGameRecv(std::vector<char> *);
  void				playerPosRecv(std::vector<char> *);
  void				playerActionRecv(std::vector<char> *);
  void				playerDieRecv(std::vector<char> *);
  void				newEnnemyRecv(std::vector<char> *);
  void				endGameRecv(std::vector<char> *);
  void				missileExploseRecv(std::vector<char> *);
  void				ennemyDieRecv(std::vector<char> *);
  void				listMapRecv(std::vector<char> *);
  void				ennemyActionRecv(std::vector<char> *);
  void				newMissileRecv(std::vector<char> *);
  void				nextFrameRecv(std::vector<char> *);
  void				playerLifeRecv(std::vector<char> *);
  void				newBonusRecv(std::vector<char> *);
  void				deleteBonusRecv(std::vector<char> *);
};

void		startGui(Client *);

typedef struct                  s_protocolFunctions
{
  ServerOpcodes                 opcode;
  void                          (Client::*protocolFunction)(std::vector<char> *);
}                               protocolFunctions;

#endif
