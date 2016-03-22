#ifndef MUSIC_H_
#define MUSIC_H_

#include <iostream>
#include <SFML/Audio.hpp>

class Music
{
	sf::SoundBuffer		_MainMenuThemeBuffer;
	sf::SoundBuffer		_MainMenuSelectionBuffer;
	sf::SoundBuffer		_GameExplosionBuffer;
	sf::SoundBuffer		_GameThemeBuffer;
	sf::Sound			_MainMenuTheme;
	sf::Sound			_MainMenuSelection;
	sf::Sound			_GameExplosion;
	sf::Sound			_GameTheme;
public:
	Music();
	~Music();
	void playMainMenuTheme();
	void stopMainMenuTheme();
	void playMenuSelectionSound();
	void playGameTheme();
	void stopGameTheme();
	void playGameExplosion();
};

#endif /* MUSIC_H_ */