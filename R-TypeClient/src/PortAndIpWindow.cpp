/*
 * PortAndIpWindow.cpp
 *
 *  Created on: 25 nov. 2014
 *      Author: Thomas
 */

#include 	"Menus.h"
#include	"Client.hh"

enum CurrentFocus
{
	IPFORM = 0,
	PORTFORM,
	CONNECTBUTTON,
	NONE
};

int					Menus::handleLeftClickPortAndIpWindow()
{
	if (_Event.mouseButton.button != sf::Mouse::Left)
		return (NONE);
	if (_Event.mouseButton.x >= 400 && _Event.mouseButton.x <= 690
			&& _Event.mouseButton.y >= 375 && _Event.mouseButton.y <= 415)
		return (IPFORM);
	if (_Event.mouseButton.x >= 400 && _Event.mouseButton.x <= 690
			&& _Event.mouseButton.y >= 550 && _Event.mouseButton.y <= 590)
		return (PORTFORM);
	if (_Event.mouseButton.x >= 30 && _Event.mouseButton.x <= 330
			&& _Event.mouseButton.y >= 330 && _Event.mouseButton.y <= 630)
		return (CONNECTBUTTON);
	return (NONE);
}

void				Menus::handleTextEnteredPortAndIpWindow(int Focus)
{
	if (_Event.text.unicode < 128)
		if (isalpha(_Event.text.unicode) || isdigit(_Event.text.unicode) || _Event.text.unicode == ' '
				|| _Event.text.unicode == '.')
		{
			if (Focus == PORTFORM && _Port.length() < 5)
			{
				_Port += _Event.text.unicode;
				std::istringstream buffer(_Port);
				buffer >> _portNb;
			}
			if (Focus == IPFORM && _Ip.length() < 15)
				_Ip += _Event.text.unicode;
		}
}

void				Menus::handleBackSpaceKeyPressedPortAndIpWindow(int Focus)
{
	if (Focus == PORTFORM && _Port.length() > 0)
		_Port.erase(_Port.end() - 1);
	if (Focus == IPFORM && _Ip.length() > 0)
		_Ip.erase(_Ip.end() - 1);
}

void				Menus::portAndIpWindow()
{
	sf::Text			IpInput = createFormText("", 450, 380);
	sf::Text			PortInput = createFormText("", 512, 556);
	sf::Texture			CurrentWindowTextures[4];
	CurrentFocus		Focus = NONE;
	std::string			path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	IpInput.setCharacterSize(30);
	CurrentWindowTextures[0].loadFromFile(path + "MenusImg/PortAndIpWindow/IpSelected.png");
	CurrentWindowTextures[1].loadFromFile(path + "MenusImg/PortAndIpWindow/PortSelected.png");
	CurrentWindowTextures[2].loadFromFile(path + "MenusImg/PortAndIpWindow/ConnectSelected.png");
	CurrentWindowTextures[3].loadFromFile(path + "MenusImg/PortAndIpWindow/PortAndIpWindow.png");
	_Font.loadFromFile(path + "Police/BMarmy.TTF");
	PortInput.setFont(_Font);
	IpInput.setFont(_Font);
	_Window.create(sf::VideoMode(800, 800), "R-Type", sf::Style::Titlebar | sf::Style::Close);
	while (_Window.isOpen())
	{
		while (_Window.pollEvent(_Event))
		 {
			if (_Event.type == sf::Event::MouseButtonPressed) {
				if (_Event.mouseButton.button == sf::Mouse::Left)
					if (_Event.mouseButton.x >= 30 && _Event.mouseButton.x <= 330
							&& _Event.mouseButton.y >= 330 && _Event.mouseButton.y <= 630)
						Focus = CONNECTBUTTON;
			}
			if (_Event.type == sf::Event::MouseButtonReleased) {
				if ((Focus = (CurrentFocus)handleLeftClickPortAndIpWindow()) != NONE) {
					this->client->getMusic()->playMenuSelectionSound();
					if (Focus == CONNECTBUTTON && client->Connection(_portNb, _Ip) == true)
						nameWindow();
				}
			}
			if (_Event.type == sf::Event::TextEntered)
				handleTextEnteredPortAndIpWindow(Focus);
			if (_Event.type == sf::Event::KeyPressed)
				if (_Event.key.code == sf::Keyboard::BackSpace)
					handleBackSpaceKeyPressedPortAndIpWindow(Focus);
				if (_Event.type == sf::Event::Closed)
				{
					client->setExit(true);
					closeWindow();
					client->sendPacket(client->getDoPacket().disconnectSnd());
				}
			PortInput.setString(_Port);
			IpInput.setString(_Ip);
			_Sprite.setTexture(CurrentWindowTextures[Focus]);
		 }
		_Window.clear();
		_Window.draw(_Sprite);
		_Window.draw(PortInput);
		_Window.draw(IpInput);
		_Window.display();
	}
}
