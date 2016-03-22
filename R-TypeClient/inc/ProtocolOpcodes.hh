//
// ProtocolOpcodes.hh for ProtocolOpcodes.hh in /home/abgral_f/dev/R-Type/inc
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Wed Nov 12 15:56:37 2014 abgral_f
// Last update Thu Nov 20 20:55:49 2014 abgral_f
//

#ifndef             PROTOCOLOPCODES_HH
# define			PROTOCOLOPCODES_HH

#ifndef				WIN32
#include			<netinet/in.h>
#else
#include			<winsock2.h>
#endif

#include			"Bonus.hh"

# define NAME_MAX_LENGTH	16
# define MAP_MAX_LENGTH		4000

enum					EnnemyType
{
	REGULAR = 0,
	CRAZY = 1
};

enum					e_action
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3,
	FIRE = 4
};

/* CLIENT PROTOCOLE OPCODES */

enum					ClientOpcodes
{
	CONNECT_REQUEST = 0x0000, //Demande d'authentification auprès du serveur
	CHOOSEN_NAME_REQUEST = 0x0001, //Requete pour choisir un nom
	CREATE_POOL_REQUEST = 0x0002, //Demande pour créer une pool
	CHOOSEN_MAP = 0x0003,	//Envoie au serveur le nom de la map choisi
	LIST_PLAYER_REQUEST = 0x0004, //Demande la liste des clients présents dans la pool
	LIST_POOL_REQUEST = 0x0005, //Demande la liste des noms des pools
	JOIN_POOL_REQUEST = 0x0006, //Demande a rejoindre la pool
	STATUS = 0x0007, //Envoie le status du client (prêt / pas prêt)
	QUIT_POOL = 0x0008, //Le client a quitter la pool
	PLAYER_ACTION = 0x0009, //Informe le serveur qu'un joueur a effectué une action
	DIE = 0x000A,	//Informe le serveur qu'un joueur est mort
	READY_TO_GAME = 0x000B,	//Informe le serveur que le joueur est prêt à lancer le jeu
	PLAYER_FINISH = 0x000C, //Informe le serveur qu'un joueur est arrivé a la fin
	LIST_MAP_REQUEST = 0x000D, //Demande la liste des maps au serveur  
	PLAYER_DISCONNECT = 0x000E, //Informe le serveur que le client se deconnecte
};

/* CLIENT PROTCOLE STRUCTS */

struct					NameInfos //CHOOSEN_NAME_REQUEST
{
	char					name[NAME_MAX_LENGTH];
};

struct					PoolNameInfos //CREATE_POOL_REQUEST && JOIN_POOL_REQUEST
{
	char					poolName[NAME_MAX_LENGTH];
};

struct					MapNameInfos //CHOOSEN_MAP
{
	char					mapName[NAME_MAX_LENGTH];
};

struct					PlayerStatusInfos // STATUS
{
	bool					isReady;
};

struct					ActionInfos //MOOVE
{
	e_action				action;
};


/* SERVER PROTOCOLE OPCODES */

enum					ServerOpcodes
{
	CONNECT_RESPONSE = 0x0000, //Envoie success ou failed
	CHOOSEN_NAME_RESPONSE = 0x0001, //Envoie success ou failed pour l'attribution d'un nom
	CREATE_POOL_RESPONSE = 0x0002, //Envoie success ou failed pourla création d'un jeu
	LIST_POOL_RESPONSE = 0x0003, //Envoie la liste des noms des pool
	PLAYER_JOIN_POOL = 0x0004, //Informe les clients qu'un joueur a rejoint la pool
	PLAYER_STATUS = 0x0005, //Informe les clients du status d'un joueur (prêt / pas prêt)
	PLAYER_QUIT = 0x0006,	//Informe les clients qu'un joueur a quitté la pool
	JOIN_POOL_RESPONSE = 0x0007, //Informe le client si il a pu rejoindre ou non la pool
	LAUNCH_GAME = 0x0008,	//Informe les clients que la partie peu débuter
	PLAYER_POS = 0x0009, //Informe la position des clients au client au debut du jeu
	ACTION = 0x000A, //Informe qu'un joueur a effectué une action
	PLAYER_DIE = 0x000B, //Informe qu'un joueur est mort
	NEW_ENNEMY = 0x000C, //Informe les joueurs qu'un nouvel ennemi est apapru
	END_GAME = 0x000D, //Informe les joueurs de la fin du jeu
	DATA_MAP = 0x000E, //Envoie le data de la map aux joueurs
	ENNEMY_DIE = 0x000F, //Informe qu'un ennemy est mort
	DISCONNECT = 0x0010, //Deconnect le client
	MISSILE_EXPLOSE = 0x0011,	//Informe qu'un missile a explosé
	LIST_MAP_RESPONSE = 0x0012, //Envoie la liste des maps au joueur
	ENNEMY_ACTION = 0x0013, //Informe qu'un joueur a effectué une action
	NEW_MISSILE = 0x0014, //Informe qu'un missile a été lancé
	NEXT_FRAME = 0x0015, //Incremente le timer
	PLAYER_LIFE = 0x0016, //Informe un joueur qu'il a perdu de la vie
	NEW_BONUS = 0x0017, //Informe qu'un bonus est apparu
	BONUS_ERASE = 0x0018, //Informe qu'un bonus a été pris
};

/* SERVER PROTOCOLE STRUCTS */

enum					e_JoinPoolResponse
{
	GAME_FULL = 0,
	GAME_DOESNT_EXIST = 1,
	SUCCESS = 2
};

typedef struct				s_ConnectInfos //CONNECT_RESPONSE
{
	bool					isSuccess;
	int					id;
}					ConnectInfos;

struct					ChoosenNameInfos //CHOOSEN_NAME_RESPONSE
{
	bool					isSuccess;
};

struct					CreatePoolInfos //CREATE_POOL_RESPONSE
{
	bool					isSuccess;
	char					name[NAME_MAX_LENGTH];
};

struct					PoolInfos // LIST_POOL_RESPONSE
{
	char					poolName[NAME_MAX_LENGTH];
};

struct					JoinPoolInfos // PLAYER_JOIN_POOL
{
	char					name[NAME_MAX_LENGTH];
	int					id;
};

struct					StatusInfos // PLAYER_STATUS
{
	bool					isReady;
	int					id;
	char					name[NAME_MAX_LENGTH];
};

struct					QuitInfos // PLAYER_QUIT
{
	int					id;
	char				name[NAME_MAX_LENGTH];
};

struct					JoinPoolRespInfos //JOIN_POOL_RESPONSE
{
	e_JoinPoolResponse			response;
	char				name[NAME_MAX_LENGTH];
};

struct					PlayerPosInfos //PLAYER_POS
{
	int					id;
	int					pos_x;
	int					pos_y;
	int					posOnCase_x;
	int					posOnCase_y;
};

struct					PlayerActionInfos //ACTION
{
	int					id;
	e_action				action;
};

struct					EnnemyActionInfos //ENNEMY_ACTION
{
	int					id;
	e_action			action;
};

struct					PlayerDieInfos //PLAYER_DIE
{
	int					id;
};

struct					NewEnnemyInfos //NEW_ENNEMY
{
	int					id;
	int					pos_x;
	int					pos_y; 
	int					posOnCase_x;
	int					posOnCase_y;
	EnnemyType			type;
};

struct					DataMapInfos //DATA_MAP
{
	char					map[MAP_MAX_LENGTH];
	int					x;
	int					y;
};

struct					EndGameInfos // END_GAME
{
	bool					isWin;
};

struct                                  EnnemyDieInfos // ENNEMY_DIE
{
	int                                   id;
};

struct					MissileExploseInfos //MISSILE_EXPLOSE
{
	int					id;
};

struct					MapInfos // LIST_MAPLIST_RESPONSE
{
	char					mapName[NAME_MAX_LENGTH];
};

struct					NewMissileInfos //NEW_MISSILE
{
	int					id;
	int					idPlayer;
	bool				isEnnemy;
	int					pos_x;
	int					pos_y;
	int					posOnCase_x;
	int					posOnCase_y;
	e_action			direction;
};

struct					PlayerLife //PLAYER_LIFE
{
	int					life;
};

struct					NewBonus //BONUS
{
	int					id;
	Type				type;
	int					posX;
	int					posY;
	int					posOnCaseX;
	int					posOnCaseY;
};

struct					BonusErase
{
	int					id;
};

#endif
