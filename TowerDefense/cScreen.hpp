#ifndef CSCREEN_HEADER
#define CSCREEN_HEADER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>

class cScreen
{
protected:
	std::map<std::string, sf::Sound*> sounds;
	std::map<std::string, sf::Color*> colors;
	

private: 
	sf::Sound sButton;
	sf::SoundBuffer buffer;
	
public:

	static sf::Music music;
	static sf::Sprite mainBg;
	static sf::Font mainFont;
	static bool isMusicOn;
	static int volk;
	static int map;
	

	cScreen();
	sf::Texture getBgTexture();
	sf::Sprite getMainBg();
	void playMainMusic();
	void stopMainMusic();
	void changeMainMusic(std::string name);
	virtual int Run(sf::RenderWindow &App) = 0;
	void setTextCenter(sf::Text &text, float yPosition);
	void setSpriteCenter(sf::Sprite &sprite, float yPosition);
	void setButtonCenter(sf::RectangleShape &rec, float yPosition);
	int onButtonHover(sf::Event Event, std::vector<sf::RectangleShape>  menuListButton, std::string type);
	void playButtonSound();
	void playSound(std::string type);
	void initSounds();
	sf::Sound* createSound(std::string name);
	void initColors();
	sf::Color getColor(std::string name);
	sf::Font getFont();

};

#endif