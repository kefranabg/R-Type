/*
 * MainMenuWindow.cpp
 *
 *  Created on: 27 nov. 2014
 *      Author: Thomas
 */

#include		"Menus.h"
#include		"Client.hh"

enum CurrentFocus
{
	CREATEROOM = 0,
	JOINROOM,
	EXIT,
	NONE
};

int				Menus::handleLeftClickMainMenuWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 390 && _Event.mouseButton.x <= 690
				&& _Event.mouseButton.y >= 380 && _Event.mouseButton.y <= 410)
		return (CREATEROOM);
	if (_Event.mouseButton.x >= 390 && _Event.mouseButton.x <= 730
				&& _Event.mouseButton.y >= 460 && _Event.mouseButton.y <= 500)
		return (JOINROOM);
	if (_Event.mouseButton.x >= 400 && _Event.mouseButton.x <= 700
					&& _Event.mouseButton.y >= 550 && _Event.mouseButton.y <= 590)
		return (EXIT);
	return (NONE);
}

void			Menus::mainMenuWindow()
{
	sf::Texture			CurrentWindowTextures[4];
	CurrentFocus		Focus;
	std::string			path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	Focus = NONE;
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/MainMenuWindow/CreateRoomSelected.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/MainMenuWindow/JoinRoomSelected.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/MainMenuWindow/ExitSelected.png");
	CurrentWindowTextures[3].loadFromFile(path + "MenusImg/MainMenuWindow/MainMenuWindow.png");
	_Window.clear();
	this->client->getMusic()->playMainMenuTheme();
	while (_Window.isOpen())
	{
		while (_Window.pollEvent(_Event))
		 {
			if (_Event.type == sf::Event::MouseButtonPressed)
				Focus = (CurrentFocus)handleLeftClickMainMenuWindow();
			if (_Event.type == sf::Event::MouseButtonReleased) {
				Focus = (CurrentFocus)handleLeftClickMainMenuWindow();
				if (Focus != NONE)
					this->client->getMusic()->playMenuSelectionSound();
				if (Focus == CREATEROOM)
					roomNameWindow();
				if (Focus == JOINROOM)
				{
					client->sendPacket(client->getDoPacket().listPoolSnd());
					joinRoomWindow();
				}
				if (Focus == EXIT)
				{
					client->setExit(true);
					closeWindow();
					client->sendPacket(client->getDoPacket().disconnectSnd());
				}
			}
			if (_Event.type == sf::Event::Closed)
			{
				client->setExit(true);
				closeWindow();
				client->sendPacket(client->getDoPacket().disconnectSnd());
			}
			_Sprite.setTexture(CurrentWindowTextures[Focus]);
		 }
		_Window.clear();
		_Window.draw(_Sprite);
		_Window.display();
	}
}
