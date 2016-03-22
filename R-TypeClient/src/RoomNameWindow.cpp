/*
 * RoomNameWindow.cpp
 *
 *  Created on: 27 nov. 2014
 *      Author: Thomas
 */

#include		"Menus.h"
#include		"Client.hh"

enum CurrentFocus
{
	ROOMNAMEFORM = 0,
	MAINMENUBUTTON,
	CONFIRMBUTTON,
	NONE
};

int					Menus::handleLeftClickRoomNameWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 390 && _Event.mouseButton.x <= 730
			&& _Event.mouseButton.y >= 460 && _Event.mouseButton.y <= 500)
		return (ROOMNAMEFORM);
	if (_Event.mouseButton.x >= 400 && _Event.mouseButton.x <= 690
			&& _Event.mouseButton.y >= 550 && _Event.mouseButton.y <= 590)
		return (MAINMENUBUTTON);
	if (_Event.mouseButton.x >= 30 && _Event.mouseButton.x <= 330
			&& _Event.mouseButton.y >= 330 && _Event.mouseButton.y <= 630)
		return (CONFIRMBUTTON);
	return (NONE);
}

void				Menus::handleTextEnteredRoomNameWindow(int Focus)
{
	if (_Event.text.unicode < 128)
		if (isalpha(_Event.text.unicode) || isdigit(_Event.text.unicode) || _Event.text.unicode == ' ')
			if (Focus == ROOMNAMEFORM && _RoomName.length() < 16)
				_RoomName += _Event.text.unicode;
}

void				Menus::handleBackSpaceKeyPressedRoomNameWindow(int Focus)
{
	if (Focus == ROOMNAMEFORM && _RoomName.length() > 0)
		_RoomName.erase(_RoomName.end() - 1);
}

void			Menus::roomNameWindow()
{
	sf::Text			RoomNameInput = createFormText("", 400, 465);
	sf::Texture			CurrentWindowTextures[4];
	CurrentFocus		Focus = NONE;
	std::string			path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/RoomNameWindow/NameSelected.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/RoomNameWindow/MainMenuSelected.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/RoomNameWindow/ConfirmSelected.png");
	CurrentWindowTextures[3].loadFromFile(path + "MenusImg/RoomNameWindow/RoomNameWindow.png");
	RoomNameInput.setFont(_Font);
	_Window.clear();
	this->_GoNextWindow = false;
	while (_Window.isOpen())
	{
		while (_Window.pollEvent(_Event))
		 {
			if (_GoNextWindow == true)
				chooseMapWindow();
			if (_Event.type == sf::Event::MouseButtonReleased) {
				if ((Focus = (CurrentFocus)handleLeftClickRoomNameWindow()) != NONE)
					this->client->getMusic()->playMenuSelectionSound();
				if (Focus == CONFIRMBUTTON && _RoomName != "")
					client->sendPacket(client->getDoPacket().createPoolSnd(_RoomName));
			}
			if (_Event.type == sf::Event::TextEntered)
				handleTextEnteredRoomNameWindow(Focus);
			if (_Event.type == sf::Event::KeyPressed)
				if (_Event.key.code == sf::Keyboard::BackSpace)
					handleBackSpaceKeyPressedRoomNameWindow(Focus);
			if (_Event.type == sf::Event::Closed)
			{
				client->setExit(true);
				closeWindow();
				client->sendPacket(client->getDoPacket().disconnectSnd());
			}
			RoomNameInput.setString(_RoomName);
			_Sprite.setTexture(CurrentWindowTextures[Focus]);
		 }
		_Window.clear();
		_Window.draw(_Sprite);
		_Window.draw(RoomNameInput);
		_Window.display();
		if (Focus == MAINMENUBUTTON)  {
			_RoomName = "";
			mainMenuWindow();
		}
	}
}
