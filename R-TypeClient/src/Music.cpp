#include "Music.h"

Music::Music()
{
	std::string		path;

#ifdef			WIN32
	path = "../../../";
#else
	path = "../";
#endif
	if (this->_MainMenuThemeBuffer.loadFromFile(path + "Sound/MainMenuTheme.ogg"))
	{
		this->_MainMenuTheme.setBuffer(this->_MainMenuThemeBuffer);
		this->_MainMenuTheme.setVolume(70);
	}
	if (this->_MainMenuSelectionBuffer.loadFromFile(path + "Sound/MainMenuSelection.ogg"))
	{
		this->_MainMenuSelection.setBuffer(this->_MainMenuSelectionBuffer);
	}
	if (this->_GameExplosionBuffer.loadFromFile(path + "Sound/GameExplosion.ogg"))
	{
		this->_GameExplosion.setBuffer(this->_GameExplosionBuffer);
	}
	if (this->_GameThemeBuffer.loadFromFile(path + "Sound/GameTheme.ogg"))
	{
		this->_GameTheme.setBuffer(this->_GameThemeBuffer);
		this->_GameTheme.setVolume(70);
	}
}

Music::~Music()
{
}

void Music::playMainMenuTheme()
{
	this->_MainMenuTheme.play();
}

void Music::stopMainMenuTheme()
{
	this->_MainMenuTheme.stop();
}

void Music::playMenuSelectionSound()
{
	this->_MainMenuSelection.play();
}

void Music::playGameTheme()
{
	this->_GameTheme.play();
}

void Music::stopGameTheme()
{
	this->_GameTheme.stop();
}

void Music::playGameExplosion()
{
	this->_GameExplosion.play();
}