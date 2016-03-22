/*
 * PlayerListWindow.cpp
 *
 *  Created on: 2 d?c. 2014
 *      Author: Thomas
 */

#include		"Menus.h"
#include		"Client.hh"

enum CurrentFocus
{
	READY = 0,
	MAINMENU,
	NONE
};

int				Menus::handleLeftClickPlayerListWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 30 && _Event.mouseButton.x <= 330
						&& _Event.mouseButton.y >= 330 && _Event.mouseButton.y <= 630)
		return (READY);
	if (_Event.mouseButton.x >= 380 && _Event.mouseButton.x <= 700
						&& _Event.mouseButton.y >= 680 && _Event.mouseButton.y <= 735)
		return (MAINMENU);
	return (NONE);
}

void			Menus::playerListWindow()
{
	sf::Texture			CurrentWindowTextures[3];
	sf::Texture			CurrentWindowHovers[4];
	sf::Text			PlayersNamesText[4];
	sf::Sprite			Hover[4];
	CurrentFocus		Focus;
	bool				isReady = false;
	std::string			path;
	unsigned int		listSize = 0;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	Focus = NONE;
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/PlayerListWindow/ReadySelected.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/PlayerListWindow/MainMenuSelected.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/PlayerListWindow/PlayerListWindow.png");
	CurrentWindowHovers[0].loadFromFile(path + "MenusImg/PlayerListWindow/Player1Hover.png");
	CurrentWindowHovers[1].loadFromFile(path + "MenusImg/PlayerListWindow/Player2Hover.png");
	CurrentWindowHovers[2].loadFromFile(path + "MenusImg/PlayerListWindow/Player3Hover.png");
	CurrentWindowHovers[3].loadFromFile(path + "MenusImg/PlayerListWindow/Player4Hover.png");
	for (unsigned int i = 0; i < 4; i++)
		Hover[i].setTexture(CurrentWindowHovers[i]);
	_Window.clear();
	_GoNextWindow = false;
	while (_Window.isOpen())
	{
		if (_GoNextWindow == true)
		{
			_Window.clear();
			_Window.display();
			this->client->getMusic()->stopMainMenuTheme();
			client->launchGameGui(&(this->_Window));
			client->sendPacket(client->getDoPacket().statusSnd(false));
			_GoNextWindow = false;
			resetPlayersStatus();
			Focus = NONE;
			isReady = !isReady;
		}
		while (_Window.pollEvent(_Event))
		 {
			if (_Event.type == sf::Event::Resized) {
				_Window.setView(sf::View(sf::FloatRect(0, 0, _Event.size.width, _Event.size.height)));
			}
			if (_Event.type == sf::Event::MouseButtonPressed)
				Focus = (CurrentFocus)handleLeftClickPlayerListWindow();
			if (_Event.type == sf::Event::MouseButtonReleased) {
				Focus = (CurrentFocus)handleLeftClickPlayerListWindow();
				if (Focus != NONE)
					this->client->getMusic()->playMenuSelectionSound();
				if (Focus == MAINMENU)
				{
					PlayersNames.clear();
					resetPlayersStatus();
					client->sendPacket(client->getDoPacket().quitPoolSnd());
					mainMenuWindow();
				}
				if (Focus == READY) {
					isReady = !isReady;
						if (isReady == false)
							Focus = NONE;
					client->sendPacket(client->getDoPacket().statusSnd(isReady));
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
		if (PlayersNames.size() != listSize)
		{
			PlayersNamesText[0] = createFormText(((PlayersNames.size() >= 1) ? PlayersNames[0] : ""), 380, 355);
			PlayersNamesText[1] = createFormText(((PlayersNames.size() >= 2) ? PlayersNames[1] : ""), 380, 435);
			PlayersNamesText[2] = createFormText(((PlayersNames.size() >= 3) ? PlayersNames[2] : ""), 380, 515);
			PlayersNamesText[3] = createFormText(((PlayersNames.size() >= 4) ? PlayersNames[3] : ""), 380, 605);
			PlayersNamesText[0].setFont(_Font);
			PlayersNamesText[1].setFont(_Font);
			PlayersNamesText[2].setFont(_Font);
			PlayersNamesText[3].setFont(_Font);
			listSize = PlayersNames.size();
		}
		_Window.draw(_Sprite);
		for (unsigned int i = 0; i < 4; i++)
		if (PlayersStatus[i] == true)
			_Window.draw(Hover[i]);
		_Window.draw(PlayersNamesText[0]);
		_Window.draw(PlayersNamesText[1]);
		_Window.draw(PlayersNamesText[2]);
		_Window.draw(PlayersNamesText[3]);
		_Window.display();
	}
}
