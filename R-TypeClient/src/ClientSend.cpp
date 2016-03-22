//
// ClientSend.cpp for ClientSend.cpp in /home/abgral_f/dev/R-Type/R-TypeServer
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Nov 17 14:34:32 2014 abgral_f
// Last update Wed Nov 19 21:14:11 2014 abgral_f
//

#include			"ClientSend.hh"

ClientSend::ClientSend()
{

}

ClientSend::~ClientSend()
{

}

std::vector<char>       *ClientSend::createData(ClientOpcodes opcode, int structSize, void *s_data) const
{
  std::vector<char>             *data = new std::vector<char>();

  data->resize(sizeof(ClientOpcodes) + structSize);
  memcpy(data->data(), &opcode, sizeof (ClientOpcodes));
  if (s_data != NULL)
    memcpy(data->data() + sizeof(ClientOpcodes), s_data, structSize);
  return (data);
}

std::vector<char>         *ClientSend::connectSnd() const
{
  return (createData(CONNECT_REQUEST, 0, NULL));
}

std::vector<char>         *ClientSend::chooseNameSnd(const std::string &name) const
{
  NameInfos			s_data;

  memset(&s_data, 0, sizeof(NameInfos));
  memcpy(s_data.name, name.c_str(), name.size());
  return (createData(CHOOSEN_NAME_REQUEST, sizeof(s_data), &s_data));
}

std::vector<char>         *ClientSend::createPoolSnd(const std::string &name) const
{
  PoolNameInfos			s_data;

  memset(&s_data, 0, sizeof(PoolNameInfos));
  memcpy(s_data.poolName, name.c_str(), name.size());
  return (createData(CREATE_POOL_REQUEST, sizeof(s_data), &s_data));
}

std::vector<char>         *ClientSend::choosenMapSnd(const std::string &name) const
{
  MapNameInfos			s_data;

  memset(&s_data, 0, sizeof(MapNameInfos));
  memcpy(s_data.mapName, name.c_str(), name.size());
  return (createData(CHOOSEN_MAP, sizeof(s_data), &s_data));
}

std::vector<char>	*ClientSend::disconnectSnd() const
{
	return (createData(PLAYER_DISCONNECT, 0, NULL));
}

std::vector<char>         *ClientSend::listPlayerSnd() const
{
  return (createData(LIST_PLAYER_REQUEST, 0, NULL));
}

std::vector<char>         *ClientSend::listPoolSnd() const
{
  return (createData(LIST_POOL_REQUEST, 0, NULL));
}

std::vector<char>         *ClientSend::joinPoolSnd(const std::string &name) const
{
  PoolNameInfos		  s_data;

  memset(&s_data, 0, sizeof(PoolNameInfos));
  memcpy(s_data.poolName, name.c_str(), name.size());
  return (createData(JOIN_POOL_REQUEST, sizeof(s_data), &s_data));
}

std::vector<char>         *ClientSend::statusSnd(bool isReady) const
{
  PlayerStatusInfos	  s_data;

  memset(&s_data, 0, sizeof(PlayerStatusInfos));
  s_data.isReady = isReady;
  return (createData(STATUS, sizeof(s_data), &s_data));
}

std::vector<char>         *ClientSend::quitPoolSnd() const
{
  return (createData(QUIT_POOL, 0, NULL));
}

std::vector<char>         *ClientSend::playerActionSnd(e_action action) const
{
  ActionInfos			s_data;

  memset(&s_data, 0, sizeof(s_data));
  s_data.action = action;
  return (createData(PLAYER_ACTION, sizeof(s_data), &s_data));
}

std::vector<char>         *ClientSend::playerDieSnd() const
{
  return (createData(DIE, 0, NULL));
}

std::vector<char>         *ClientSend::readyToGameSnd() const
{
  return (createData(READY_TO_GAME, 0, NULL));
}

std::vector<char>         *ClientSend::playerFinishSnd() const
{
  return (createData(PLAYER_FINISH, 0, NULL));
}

std::vector<char>         *ClientSend::listMapSnd() const
{
	return (createData(LIST_MAP_REQUEST, 0, NULL));
}