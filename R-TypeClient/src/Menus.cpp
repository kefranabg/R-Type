/*
 * Menus.cpp
 *
 *  Created on: 25 nov. 2014
 *      Author: Thomas
 */

#include "Menus.h"
#include "Client.hh"

Menus::Menus(Client *_client) {
	// TODO Auto-generated constructor stub
	this->client = _client;
	this->_GoNextWindow = false;
	for (unsigned int i = 0; i < 4; i++)
		this->PlayersStatus.push_back(false);
}

Menus::~Menus() {
	// TODO Auto-generated destructor stub
}

void				Menus::setGoNextWindow(bool value)
{
	this->_GoNextWindow = value;
}

const std::string& 	Menus::getIp() const
{
	return (_Ip);
}

const std::string& 	Menus::getName() const
{
	return (_Name);
}

const std::string& 	Menus::getPort() const
{
	return (_Port);
}

const std::string& 	Menus::getRoomName() const
{
	return (_RoomName);
}

const std::string&	Menus::getJoinedRoom() const
{
	return (_JoinedRoom);
}

int					Menus::getChosenMap() const
{
	return (_ChosenMap);
}

void				Menus::startNewMenu()
{
	portAndIpWindow();
}

void				Menus::closeWindow()
{
	_Window.close();
}

void				Menus::addPlayerToList(const std::string &name)
{
	PlayersNames.push_back(name);
}

void				Menus::delPlayerInList(const std::string &name)
{
	for (unsigned int i = 0; i < PlayersNames.size(); i++)
	{
		if (PlayersNames[i] == name)
			PlayersNames.erase(PlayersNames.begin() + i);
	}
}

void				Menus::addRoomToList(const std::string &name)
{
	RoomsNames.push_back(name);
}

void				Menus::delRoomInList(const std::string &name)
{
	for (unsigned int i = 0; i < RoomsNames.size(); i++)
	{
		if (RoomsNames[i] == name)
			RoomsNames.erase(RoomsNames.begin() + i);
	}
}

sf::Text			Menus::createFormText(std::string Text, int posX, int posY)
{
	sf::Text		PortFormText;

	PortFormText.setString(Text);
	PortFormText.setCharacterSize(30);
	PortFormText.setColor(sf::Color(82, 211, 255));
	PortFormText.setStyle(sf::Text::Regular);
	PortFormText.setPosition(static_cast<float>(posX), static_cast<float>(posY));
	return (PortFormText);
}

void				Menus::updatePlayerStatus(const std::string &name, bool status)
{
	for (unsigned int i = 0; i < PlayersNames.size(); i++)
	{
		if (PlayersNames[i] == name && i < 4)
			PlayersStatus[i] = status;
	}
}

void				Menus::resetPlayersStatus()
{
	for (unsigned int i = 0; i < PlayersStatus.size(); i++)
		PlayersStatus[i] = false;
}