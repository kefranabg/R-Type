/*
 * PopupGeneration.cpp
 *
 *  Created on: 26 nov. 2014
 *      Author: Thomas
 */

#include		"Menus.h"

void			Menus::popupGeneration(std::string Message)
{
	sf::Text			PopupMessage = createFormText(Message, 100, 150);
	sf::Texture			CurrentWindowTexture;
	sf::RenderWindow	Window;
	std::string			path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	CurrentWindowTexture.loadFromFile(path + "MenusImg/PopupWindow/PopupWindow.png");
	Window.create(sf::VideoMode(450, 350), "R-Type", sf::Style::Titlebar | sf::Style::Close);
	_Sprite.setTexture(CurrentWindowTexture);
	PopupMessage.setFont(_Font);
	Window.draw(_Sprite);
	Window.draw(PopupMessage);
	Window.display();
	while (Window.isOpen())
		while (Window.pollEvent(_Event))
			if (_Event.type == sf::Event::Closed)
				Window.close();
}
