
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdio.h>
#include <vector>

#include "cScreen.hpp"
#include "BodenGegner.h"
#include "Map.h"
#include "Turm.h"
#include "Einheit.h"
#include "globals.hpp"

class screen_4 : public cScreen
{
private:

	const float headerHeight = 60.f;

	int waves = 30;
	int waveCount = 0;
	int waveTimeEnd = 5000;

	int enemySpawn = 5;

	int life = 100;

	int gold = 300;

	int timePrev = -1;
	int milli = 0;

	int seconds = 0;

	bool wavesEnded = false;

	sf::Text waveText;
	sf::Text lifeText;
	sf::Text goldText;
	sf::Clock waveClock;


	Map *karte;
	sf::Sprite feldSprite;
	sf::Sprite gegnerSprite;
	sf::Sprite turmSprite;
	sf::RenderWindow *window;
	std::vector<Einheit*> türme;
	std::vector<BodenGegner*> gegner;
	BodenGegner *gegner1;
	Turm *turm1;
	void drawMap(sf::RenderWindow *app);
	void drawGegner(sf::RenderWindow *app);
	void drawTürme(sf::RenderWindow *app);
	void löschePositionen();
	void löscheToteEinheiten();
	void löscheAlleEinheiten();


public:
	screen_4(void);
	virtual int Run(sf::RenderWindow &App);
	std::string getWaveText(int count, int max);
	std::string getLiveText(int count);
	std::string getGoldText(int count);
	std::string getTimeText(int seconds);
	void increaseWave();
	bool checkWaveSpaming();
	void spawnWave();
	void decreaseLife(int count);
	bool died();
	void increaseGold(int value);
	void decreaseGold(int value);
	bool isGoldAvailable(int value);
};
