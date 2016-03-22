/*
 * NameWindow.cpp
 *
 *  Created on: 26 nov. 2014
 *      Author: Thomas
 */

#include		"Menus.h"
#include		"Client.hh"

enum CurrentFocus
{
	NAMEFORM = 0,
	CONFIRMBUTTON,
	NONE
};

int					Menus::handleLeftClickNameWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 400 && _Event.mouseButton.x <= 750
			&& _Event.mouseButton.y >= 460 && _Event.mouseButton.y <= 500)
		return (NAMEFORM);
	if (_Event.mouseButton.x >= 30 && _Event.mouseButton.x <= 330
			&& _Event.mouseButton.y >= 330 && _Event.mouseButton.y <= 630)
		return (CONFIRMBUTTON);
	return (NONE);
}

void				Menus::handleTextEnteredNameWindow(int Focus)
{
	if (_Event.text.unicode < 128)
		if (isalpha(_Event.text.unicode) || isdigit(_Event.text.unicode) || _Event.text.unicode == ' ')
			if (Focus == NAMEFORM && _Name.length() < 16)
				_Name += _Event.text.unicode;
}

void				Menus::handleBackSpaceKeyPressedNameWindow(int Focus)
{
	if (Focus == NAMEFORM && _Name.length() > 0)
		_Name.erase(_Name.end() - 1);
}

void			Menus::nameWindow()
{
	sf::Text			NameInput = createFormText("", 400, 460);
	sf::Texture			CurrentWindowTextures[3];
	CurrentFocus		Focus = NONE;
	std::string			path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/NameWindow/NameSelected.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/NameWindow/ConfirmSelected.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/NameWindow/NameWindow.png");
	NameInput.setFont(_Font);
	_Window.clear();
	this->_GoNextWindow = false;
	while (_Window.isOpen())
	{
		if (this->_GoNextWindow == true)
			mainMenuWindow();
		while (_Window.pollEvent(_Event))
		 {
			if (_Event.type == sf::Event::MouseButtonPressed) {
				if (_Event.mouseButton.button == sf::Mouse::Left)
					if (_Event.mouseButton.x >= 30 && _Event.mouseButton.x <= 330
							&& _Event.mouseButton.y >= 330 && _Event.mouseButton.y <= 630)
						Focus = CONFIRMBUTTON;
			}
			if (_Event.type == sf::Event::MouseButtonReleased) {
				if ((Focus = (CurrentFocus)handleLeftClickNameWindow()) != NONE) {
					this->client->getMusic()->playMenuSelectionSound();
					if (Focus == CONFIRMBUTTON && _Name != "")
						client->sendPacket(client->getDoPacket().chooseNameSnd(_Name));
				}
			}
			if (_Event.type == sf::Event::TextEntered)
				handleTextEnteredNameWindow(Focus);
			if (_Event.type == sf::Event::KeyPressed)
				if (_Event.key.code == sf::Keyboard::BackSpace)
					handleBackSpaceKeyPressedNameWindow(Focus);
			if (_Event.type == sf::Event::Closed)
			{
				client->setExit(true);
				closeWindow();
				client->sendPacket(client->getDoPacket().disconnectSnd());
			}
			NameInput.setString(_Name);
			_Sprite.setTexture(CurrentWindowTextures[Focus]);
		 }
		_Window.clear();
		_Window.draw(_Sprite);
		_Window.draw(NameInput);
		_Window.display();
	}
}
