/*
 * JoinRoomWindow.cpp
 *
 *  Created on: 1 d?c. 2014
 *      Author: Thomas
 */

#include		"Menus.h"
#include		"Client.hh"

enum CurrentFocus
{
	MAINMENU = 0,
	ROOM1,
	ROOM2,
	ROOM3,
	ROOM4,
	NONE
};

int				Menus::handleLeftClickJoinRoomWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 360 && _Event.mouseButton.x <= 770
				&& _Event.mouseButton.y >= 350 && _Event.mouseButton.y <= 400)
		return (ROOM1);
	if (_Event.mouseButton.x >= 360 && _Event.mouseButton.x <= 770
					&& _Event.mouseButton.y >= 430 && _Event.mouseButton.y <= 475)
		return (ROOM2);
	if (_Event.mouseButton.x >= 360 && _Event.mouseButton.x <= 770
						&& _Event.mouseButton.y >= 510 && _Event.mouseButton.y <= 560)
		return (ROOM3);
	if (_Event.mouseButton.x >= 360 && _Event.mouseButton.x <= 770
						&& _Event.mouseButton.y >= 600 && _Event.mouseButton.y <= 650)
		return (ROOM4);
	if (_Event.mouseButton.x >= 380 && _Event.mouseButton.x <= 700
						&& _Event.mouseButton.y >= 680 && _Event.mouseButton.y <= 735)
		return (MAINMENU);
	return (NONE);
}

void			Menus::joinRoomWindow()
{
	sf::Texture			CurrentWindowTextures[6];
	sf::Text			RoomsNamesText[4];
	CurrentFocus		Focus;
	std::string			path;
	unsigned int		listSize = 0;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	Focus = NONE;
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/JoinRoomWindow/MainMenuSelected.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/JoinRoomWindow/Room1Selected.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/JoinRoomWindow/Room2Selected.png");
	CurrentWindowTextures[3].loadFromFile(path + "MenusImg/JoinRoomWindow/Room3Selected.png");
	CurrentWindowTextures[4].loadFromFile(path + "MenusImg/JoinRoomWindow/Room4Selected.png");
	CurrentWindowTextures[5].loadFromFile(path + "MenusImg/JoinRoomWindow/JoinRoomWindow.png");
	_Window.clear();
	_GoNextWindow = false;
	while (_Window.isOpen())
	{
		if (_GoNextWindow == true)
		{
			RoomsNames.clear();
			playerListWindow();
		}
		while (_Window.pollEvent(_Event))
		 {
			if (_Event.type == sf::Event::MouseButtonPressed)
				Focus = (CurrentFocus)handleLeftClickJoinRoomWindow();
			if (_Event.type == sf::Event::MouseButtonReleased) {
				Focus = (CurrentFocus)handleLeftClickJoinRoomWindow();
				if (Focus != NONE)
					this->client->getMusic()->playMenuSelectionSound();
				if (Focus == MAINMENU)
				{
					RoomsNames.clear();
					mainMenuWindow();
				}
				if (Focus >= ROOM1 && Focus <= ROOM4) {
					if (RoomsNames.size() >= static_cast<unsigned int>(Focus)) {
						_JoinedRoom = RoomsNames[Focus - 1];
						client->sendPacket(client->getDoPacket().joinPoolSnd(_JoinedRoom));
					}
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
		if (RoomsNames.size() != listSize)
		{
			RoomsNamesText[0] = createFormText(((RoomsNames.size() >= 1) ? RoomsNames[0] : ""), 380, 355);
			RoomsNamesText[1] = createFormText(((RoomsNames.size() >= 2) ? RoomsNames[1] : ""), 380, 435);
			RoomsNamesText[2] = createFormText(((RoomsNames.size() >= 3) ? RoomsNames[2] : ""), 380, 515);
			RoomsNamesText[3] = createFormText(((RoomsNames.size() >= 4) ? RoomsNames[3] : ""), 380, 605);
			RoomsNamesText[0].setFont(_Font);
			RoomsNamesText[1].setFont(_Font);
			RoomsNamesText[2].setFont(_Font);
			RoomsNamesText[3].setFont(_Font);
			listSize = RoomsNames.size();
		}
		_Window.draw(_Sprite);
		_Window.draw(RoomsNamesText[0]);
		_Window.draw(RoomsNamesText[1]);
		_Window.draw(RoomsNamesText[2]);
		_Window.draw(RoomsNamesText[3]);
		_Window.display();
	}
}
