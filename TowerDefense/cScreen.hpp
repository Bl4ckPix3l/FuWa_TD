#ifndef CSCREEN_HEADER
#define CSCREEN_HEADER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Map.h"

class cScreen
{
protected:
	std::map<std::string, sf::Sound*> sounds;
	std::map<std::string, sf::Color*> colors;

	sf::Font* mainFont;

private: 
	sf::Sound sButton;
	sf::SoundBuffer buffer;
	sf::Texture Texture;
	std::string bgMain = "media/img/main.png";
	
public:
	static std::map<std::string, std::string>* selectedRace;
	static std::map<std::string, std::string>* selectedMap;

	static sf::Music music;
	static sf::Sprite mainBg;
	static bool isMusicOn;

	static bool isPlaying;

	cScreen();
	~cScreen();
	
	void initColors();
	void initSounds();

	void playMainMusic();
	void stopMainMusic();
	void changeMainMusic(std::string name);
	virtual int Run(sf::RenderWindow &App) = 0;
	void setTextCenter(sf::Text &text, float yPosition);
	void setSpriteCenter(sf::Sprite &sprite, float yPosition);
	void setButtonCenter(sf::RectangleShape &rec, float yPosition);
	void playSound(std::string type);
	void setBgTexture(std::string name);
	void drawTexture(sf::RenderWindow *app);

	int onButtonHover(sf::Event Event, std::vector<sf::RectangleShape*>  menuListButton, std::string type);
	int onButtonHover(sf::Event Event, std::vector<sf::CircleShape*>  menuListButton, std::string type);
	Position* onFieldHover(sf::Event Event, Map* karte, std::string type);
	sf::Sound* createSound(std::string name);

	sf::Font* getMainFont();
	sf::Color getColor(std::string name);
	sf::Texture getBgTexture();
	sf::Sprite getMainBg();
};

#endif