
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
#include "functions.h"
#include "Model.h"

class screen_4 : public cScreen
{
private:

	const float headerHeight = 60.f;

	int waves = 0;
	int waveCount = 0;
	int waveTimeEnd = 10000;

	int life = 100;

	int gold = 300;

	int timePrev = -1;
	int milli = 0;

	int towers = 3;
	
	int seconds = 0;

	bool wavesEnded = false;
	int kills;
	sf::Text waveText;
	sf::Text lifeText;
	sf::Text goldText;
	sf::Clock waveClock;
	sf::Clock moveClock;

	std::vector<sf::CircleShape *> towerIcons;
	std::vector<sf::RectangleShape *> enemyMapIcon;
	std::vector<sf::RectangleShape *> towerMapIcon;
	std::vector<sf::RectangleShape *> mapFields;
	
	std::map<std::string, std::string>* dbTower;
	std::vector<std::map<std::string, std::string>*> dbTowers;
	std::vector<std::map<std::string, std::string>*> dbWaves;

	Map *karte;
	sf::Sprite feldSprite;
	sf::Sprite gegnerSprite;
	sf::Sprite turmSprite;
	sf::RenderWindow *window;
	std::vector<Turm*> türme;
	std::vector<BodenGegner*> gegner;
	BodenGegner *gegner1;
	Turm *turm1;
	void drawMap(sf::RenderWindow *app);
	void drawGegner(sf::RenderWindow *app);
	void drawTürme(sf::RenderWindow *app);
	void drawTowerIcons(sf::RenderWindow *app);
	void löschePositionen();
	void löscheToteEinheiten();
	void löscheAlleEinheiten();
	void initShapes();

	std::vector<Turm*> angreiffendeEinheiten;
	void löscheShapes();

	sf::RectangleShape* field;
	sf::CircleShape* tower;
	sf::RectangleShape* enemy;
	Position *tempPos;
	Turm* newTower;
	int movingEnemy;
	int pathCounter;
	
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

	std::string screen_4::getResultsValue(std::map<std::string, std::string>* map, std::string name);
};
