/*
 * Menus.h
 *
 *  Created on: 25 nov. 2014
 *      Author: Thomas
 */

#ifndef MENUS_H_
#define MENUS_H_

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class			Client;

class Menus {
public:
	Menus(Client *);
	virtual ~Menus();

	void				startNewMenu();

	const std::string& 	getIp() const;
	const std::string& 	getName() const;
	const std::string& 	getPort() const;
	const std::string& 	getRoomName() const;
	const std::string&	getJoinedRoom() const;
	int					getChosenMap() const;
	void				setGoNextWindow(bool);
	void				closeWindow();
	sf::Text			createFormText(std::string, int, int);

	void				portAndIpWindow();
	int					handleLeftClickPortAndIpWindow();
	void				handleTextEnteredPortAndIpWindow(int);
	void				handleBackSpaceKeyPressedPortAndIpWindow(int);

	void				popupGeneration(std::string);

	void				nameWindow();
	int					handleLeftClickNameWindow();
	void				handleTextEnteredNameWindow(int);
	void				handleBackSpaceKeyPressedNameWindow(int);

	void				mainMenuWindow();
	int					handleLeftClickMainMenuWindow();
	void				handleTextEnteredMainMenuWindow(int);
	void				handleBackSpaceKeyPressedMainMenuWindow(int);

	void				roomNameWindow();
	int					handleLeftClickRoomNameWindow();
	void				handleTextEnteredRoomNameWindow(int);
	void				handleBackSpaceKeyPressedRoomNameWindow(int);

	void				joinRoomWindow();
	int					handleLeftClickJoinRoomWindow();

	void				playerListWindow();
	int					handleLeftClickPlayerListWindow();

	void				chooseMapWindow();
	int					handleLeftClickChooseMapWindow();

	void				addPlayerToList(const std::string &);
	void				delPlayerInList(const std::string &);

	void				addRoomToList(const std::string &);
	void				delRoomInList(const std::string &);

	void				updatePlayerStatus(const std::string &, bool);
	void				resetPlayersStatus();

private:
	sf::RenderWindow	_Window;
	sf::Event			_Event;
	sf::Sprite			_Sprite;
	sf::Font			_Font;
	std::string			_Port;
	std::string			_Ip;
	std::string			_Name;
	std::string			_RoomName;
	std::string			_JoinedRoom;
	int					_portNb;
	int					_ChosenMap;
	bool				_GoNextWindow;
	std::vector<std::string>	PlayersNames;
	std::vector<std::string>	RoomsNames;
	std::vector<bool>			PlayersStatus;
	Client				*client;
};

#endif /* MENUS_H_ */
