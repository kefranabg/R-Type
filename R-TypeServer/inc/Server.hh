
#ifndef				SERVER_HH_
# define			SERVER_HH_


#include		    <csignal>
#include			<vector>

#include			"ClientInfo.hh"
#include			"Select.hh"
#include			"ServerSend.hh"

# ifdef				WIN32
#include			"_dirent.h"
#include			"WinSocket.hh"
#include			"WinThread.hh"
#include			<signal.h>
#include			<stdlib.h>
#include			<tchar.h>
#else
#include			<dirent.h>
#include			<sstream>
#include			<sys/types.h>
#include			<sys/socket.h>
#include			<netdb.h>
#include			"UnixSocket.hh"
#include			"UnixThread.hh"
#endif

#include			<fstream>

class				Game;

/* DEFINES */

# define QUIT_CMD		"quit"
# define MAX_CLIENTS		400
# define MAX_ROOM			100
# define TV_USEC		500000
# define SIZE_MAX_PACKET	4096
# define MAX_MAP_SIZE 4000
# define MAP_SUCCESS "success"
# define MAP_HEIGHT 14
# define MAP_LENGTH 30
# define NB_OPCODES			15
# define DEFAULT_SOCKET		27015

/* ERRORS */

# define INIT_ERROR		"Server initialization error"
# define SELECT_ERROR		"Select error"
# define READ_SOCKET_ERROR	"Error on recvfrom"
# define WRITE_SOCKET_ERROR     "Error on sendto"
# define WRONG_PACKET		"Wrong packet"
# define UNKNOWN_CLIENT		"Unknown client"


class				Server
{
private:
  ASocket			*socket;
  Select			select;
  struct timeval                tv;
  std::vector<ClientInfo *>	clients;
  std::vector<Game *>		threadPools;
  ServerSend			doPacket;
public:
  Server();
  ~Server();
  void				start();
  void				checkInput();
  void				initSelect();
  void				processPacketReception();
  ClientOpcodes			getOpcode(const std::vector<char> &) const;
  packetRecv			*getMsg();
  void                          sendPacket(const std::vector<char> *,
					   struct sockaddr_in *) const;
  void				disconnectClient(int, bool);
  ClientInfo                    *getClientByAddr(struct sockaddr_in *) const;
  int				assignRoomId() const;
  std::vector<std::vector<char>> *getMapData(std::string const &mapName);
  std::string const				isMapValid(std::vector<std::vector<char>> const *map);
  std::vector<std::string>			*getFilesList(std::string const &pathName);
  const ServerSend						&getDoPacket() const;

  /* Handle packets recieved */
  void				connectRecv(packetRecv *);
  void				chooseNameRecv(packetRecv *);
  void				createPoolRecv(packetRecv *);
  void				choosenMapRecv(packetRecv *);
  void				listPlayerRecv(packetRecv *);
  void				listPoolRecv(packetRecv *);
  void				joinPoolRecv(packetRecv *);
  void				statusRecv(packetRecv *);
  void				quitPoolRecv(packetRecv *);
  void				playerActionRecv(packetRecv *);
  void				playerDieRecv(packetRecv *);
  void				readyToGameRecv(packetRecv *);
  void				playerFinishRecv(packetRecv *);
  void				listMapRecv(packetRecv *);
  void				disconnectRecv(packetRecv *);
};

typedef struct                  s_protocolFunctions
{
  ClientOpcodes                 opcode;
  void                          (Server::*protocolFunction)(packetRecv *);
}                               protocolFunctions;

#endif
