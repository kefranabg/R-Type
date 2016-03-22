/*
 * ChoiceMapWindow.cpp
 *
 *  Created on: 4 d?c. 2014
 *      Author: Thomas
 */

#include 	"Menus.h"
#include	"Client.hh"

enum CurrentFocus
{
	NONE = 0,
	MAP1BUTTON,
	MAP2BUTTON,
	MAP3BUTTON,
	MAP4BUTTON
};

int						Menus::handleLeftClickChooseMapWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 165 && _Event.mouseButton.x <= 355
		&& _Event.mouseButton.y >= 335 && _Event.mouseButton.y <= 460)
		return(MAP1BUTTON);
	if (_Event.mouseButton.x >= 445 && _Event.mouseButton.x <= 635
		&& _Event.mouseButton.y >= 335 && _Event.mouseButton.y <= 460)
		return (MAP2BUTTON);
	if (_Event.mouseButton.x >= 165 && _Event.mouseButton.x <= 355
		&& _Event.mouseButton.y >= 555 && _Event.mouseButton.y <= 680)
		return (MAP3BUTTON);
	if (_Event.mouseButton.x >= 445 && _Event.mouseButton.x <= 635
		&& _Event.mouseButton.y >= 555 && _Event.mouseButton.y <= 680)
		return (MAP4BUTTON);
	return (NONE);
}

void				Menus::chooseMapWindow()
{
	sf::Texture			CurrentWindowTextures[5];
	CurrentFocus		Focus = NONE;
	std::string			path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/ChoiceMapWindow/ChoiceMapWindow.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/ChoiceMapWindow/Map1.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/ChoiceMapWindow/Map2.png");
	CurrentWindowTextures[3].loadFromFile(path + "MenusImg/ChoiceMapWindow/Map3.png");
	CurrentWindowTextures[4].loadFromFile(path + "MenusImg/ChoiceMapWindow/Map4.png");
	_Window.clear();
	while (_Window.isOpen())
	{
		while (_Window.pollEvent(_Event))
		{
			if (_Event.type == sf::Event::MouseButtonPressed)
				Focus = (CurrentFocus)handleLeftClickChooseMapWindow();
			if (_Event.type == sf::Event::MouseButtonReleased) {
				if ((Focus = (CurrentFocus)handleLeftClickChooseMapWindow()) != NONE) {
					this->client->getMusic()->playMenuSelectionSound();
					_ChosenMap = Focus;
					if (Focus == MAP1BUTTON)
					client->sendPacket(client->getDoPacket().choosenMapSnd("map.txt"));
					if (Focus == MAP2BUTTON)
					client->sendPacket(client->getDoPacket().choosenMapSnd("map2.txt"));
					if (Focus == MAP3BUTTON)
					client->sendPacket(client->getDoPacket().choosenMapSnd("map3.txt"));
					if (Focus == MAP4BUTTON)
					client->sendPacket(client->getDoPacket().choosenMapSnd("map3.txt"));
					playerListWindow();
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
