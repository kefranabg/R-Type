//
// ServerSend.cpp for ServerSend.cpp in /home/abgral_f/dev/R-Type/R-TypeServer
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Nov 17 13:42:34 2014 abgral_f
// Last update Thu Nov 20 18:34:50 2014 abgral_f
//

#include			"ServerSend.hh"

ServerSend::ServerSend()
{

}

ServerSend::~ServerSend()
{

}

std::vector<char>       *ServerSend::createData(ServerOpcodes opcode, int structSize, void *s_data) const
{
  std::vector<char>             *data = new std::vector<char>();

  data->resize(sizeof(ServerOpcodes) + structSize);
  memcpy(data->data(), &opcode, sizeof (ServerOpcodes));
  if (s_data != NULL)
    memcpy(data->data() + sizeof(ServerOpcodes), s_data, structSize);
  return (data);
}

std::vector<char>       *ServerSend::connectSnd(bool isSuccess, int id) const
{
  ConnectInfos                  s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {isSuccess, id};
  return (createData(CONNECT_RESPONSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::chooseNameSnd(bool isSuccess) const
{
  ChoosenNameInfos              s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {isSuccess};
  return (createData(CHOOSEN_NAME_RESPONSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::disconnectSnd() const
{
  return (createData(DISCONNECT, 0, NULL));
}

std::vector<char>	*ServerSend::createPoolSnd(bool isSuccess, const std::string &name) const
{
  CreatePoolInfos               s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data.isSuccess = isSuccess;
  for (unsigned int i = 0; i < name.size(); i++)
	  s_data.name[i] = name[i];
  return (createData(CREATE_POOL_RESPONSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::listPoolSnd(const std::string &name) const
{
  PoolInfos	                s_data;

  memset(&s_data, 0, sizeof(s_data));
  memcpy(s_data.poolName, name.c_str(), name.size());
  return (createData(LIST_POOL_RESPONSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::playerJoinPoolSnd(const std::string &name, int id) const
{
  JoinPoolInfos	                s_data;

  memset(&s_data, 0, sizeof(s_data));
  memcpy(s_data.name, name.c_str(), name.size());
  s_data.id = id;
  return (createData(PLAYER_JOIN_POOL, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::joinPoolSnd(e_JoinPoolResponse response, const std::string &name) const
{
  JoinPoolRespInfos     s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data.response = response;
  for (unsigned int i = 0; i < name.size(); i++)
	  s_data.name[i] = name[i];
  return (createData(JOIN_POOL_RESPONSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::playerStatusSnd(bool isReady, int id, const std::string &name) const
{
  StatusInfos		s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data.isReady = isReady;
  s_data.id = id;
  for (unsigned int i = 0; i < name.size(); i++)
	  s_data.name[i] = name[i];
  return (createData(PLAYER_STATUS, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::playerQuitSnd(int id, const std::string &name) const
{
  QuitInfos		s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data.id = id;
  for (unsigned int i = 0; i < name.size(); i++)
	  s_data.name[i] = name[i];
  return (createData(PLAYER_QUIT, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::launchGameSnd() const
{
  return (createData(LAUNCH_GAME, 0, NULL));
}

std::vector<char>	*ServerSend::playerPosSnd(int id, int posX, int posY,
						  int posOnCaseX, int posOnCaseY) const
{
  PlayerPosInfos		s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {id, posX, posY, posOnCaseX, posOnCaseY};
  return (createData(PLAYER_POS, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::playerActionSnd(int id, e_action action) const
{
  PlayerActionInfos	s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {id, action};
  return (createData(ACTION, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::playerDieSnd(int id) const
{
  PlayerDieInfos	s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {id};
  return (createData(PLAYER_DIE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::newEnnemySnd(int id, int posX, int posY,
                                                  int posOnCaseX, int posOnCaseY, EnnemyType type) const
{
  NewEnnemyInfos	s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {id, posX, posY, posOnCaseX, posOnCaseY, type};
  return (createData(NEW_ENNEMY, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::endGameSnd(bool isWin) const
{
  EndGameInfos		s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {isWin};
  return (createData(END_GAME, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::dataMapSnd(std::vector<std::vector<char>> *map) const
{
  DataMapInfos		s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data.y = map->size();
  s_data.x = map->back().size();
  for (int y = 0; y < s_data.y; y++)
	  for (int x = 0; x < s_data.x; x++)
		  s_data.map[y * s_data.x + x] = map->at(y).at(x);
  return (createData(DATA_MAP, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::missileExploseSnd(int id) const
{
  MissileExploseInfos	s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {id};
  return (createData(MISSILE_EXPLOSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::ennemyDieSnd(int id) const
{
  EnnemyDieInfos	s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data = {id};
  return (createData(ENNEMY_DIE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::listMapSnd(const std::string &name) const
{
	MapInfos	s_data;

	memset(&s_data, 0, sizeof(s_data));
	memcpy(s_data.mapName, name.c_str(), name.size());
	return (createData(LIST_MAP_RESPONSE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::ennemyActionSnd(int id, e_action action) const
{
	EnnemyActionInfos	s_data;

	memset(&s_data, 0, sizeof(s_data));
	s_data = { id, action };
	return (createData(ENNEMY_ACTION, sizeof(s_data), &s_data));
}

std::vector<char>		*ServerSend::newMissileSnd(int id, int idPlayer, bool isEnnemy,
										int posX, int posY, int posOnCaseX,
										int posOnCaseY, e_action direction) const
{
	NewMissileInfos		s_data;

	memset(&s_data, 0, sizeof(s_data));
	s_data = {id, idPlayer, isEnnemy, posX, posY, posOnCaseX,
				posOnCaseY, direction};
	return (createData(NEW_MISSILE, sizeof(s_data), &s_data));
}

std::vector<char>	*ServerSend::nextFrameSnd() const
{
	return (createData(NEXT_FRAME, 0, NULL));
}

std::vector<char>		*ServerSend::playerLifeSnd(int life) const
{
	PlayerLife		s_data;

	memset(&s_data, 0, sizeof(s_data));
	s_data = { life };
	return (createData(PLAYER_LIFE, sizeof(s_data), &s_data));
}

std::vector<char>		*ServerSend::newBonusSnd(Type type, int posX, int posY, int posOnCaseX, int posOnCaseY, int id) const
{
	NewBonus		s_data;

	memset(&s_data, 0, sizeof(s_data));
	s_data = { id, type, posX, posY, posOnCaseX, posOnCaseY };
	return (createData(NEW_BONUS, sizeof(s_data), &s_data));
}

std::vector<char>		*ServerSend::deleteBonusSnd(int id) const
{
	BonusErase		s_data;

	memset(&s_data, 0, sizeof(s_data));
	s_data = { id };
	return (createData(BONUS_ERASE, sizeof(s_data), &s_data));
}
