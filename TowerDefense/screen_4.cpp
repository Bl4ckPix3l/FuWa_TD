#include <iostream>
#include "cScreen.hpp"
#include "globals.hpp"
#include "screen_4.hpp"


#define POSGRÖßE 64

screen_4::screen_4(void)
{

}

std::string screen_4::getWaveText(int count, int max){
	char buffer [50];
	sprintf(buffer, "Welle: %d / %d", count, max);
	return buffer;
}

std::string screen_4::getLiveText(int count){
	char buffer[50];
	sprintf(buffer, "Leben: %d", count);
	return buffer;
}

std::string screen_4::getGoldText(int count){
	char buffer[50];
	sprintf(buffer, "Gold: %d", count);
	return buffer;
}

std::string screen_4::getTimeText(int sec){
	int minutes = std::round(sec / 60);
	int secs = sec - (minutes * 60);

	char buffer[50];

	std::string format; 
	if (secs < 10){
		format = "%d:0%d";
	}
	else {
		format = "%d:%d";
	}

	sprintf(buffer, format.c_str(), minutes, secs);
	return buffer;
}

void screen_4::increaseWave(){
	if (checkWaveSpaming()){
		waveCount++;
		waveText.setString(getWaveText(waveCount, waves));
	}
}

bool screen_4::checkWaveSpaming(){
	if (waveCount == waves){
		wavesEnded = true;
		return false;
	}
	return true;
}

void screen_4::spawnWave(){
	
	for (int i = 0; i < enemySpawn; i++){
		BodenGegner *enemy = new BodenGegner();
		enemy->setMaxLeben(40);
		enemy->setLeben(enemy->getMaxLeben());
		enemy->setSpeed(1);
		enemy->spawn(karte->getStartPosition());
		gegner.push_back(enemy);
		movingEnemy = 1;
		pathCounter = 0;
		kills = 0;
	}

	increaseWave();
	playSound("spawn1");
	timePrev = -1;
	milli = 0;
}

void screen_4::decreaseLife(int count){
	if (!died()){
		life -= count;
		if (life <= 0){
			playSound("gameover");
			life = 0;
		}

		if (life <=  25){
			lifeText.setColor(sf::Color(184, 16, 12));
		}
		else if (life <= 50){
			lifeText.setColor(sf::Color(182, 184, 12));
		}
		playSound("lifeDec");

		lifeText.setString(getLiveText(life));
	}
}

bool screen_4::died(){
	if (life <= 0){
		return true;
	}
	return false;
}

void screen_4::increaseGold(int value){
	gold += value;
};

void screen_4::decreaseGold(int value){
	if (isGoldAvailable(value)){
		gold -= value;
		goldText.setString(getGoldText(gold));
	}
	else {
		playSound("money");
	}
}

bool screen_4::isGoldAvailable(int value){
	int goldDif = gold - value;
	bool state = true;
	if (goldDif < 0){
		state = false;
	}
	return state;
}

int screen_4::Run(sf::RenderWindow &app)
{
	sf::Event Event;
	sf::Font font;
	sf::Text txtTime;
	sf::Clock clock;

	sf::Time time;
	sf::Time clockTime;

	bool Running = true;
	
	float progressWidth = 120;
	float progressHeight = 50;
	float progressSteps = progressWidth / waveTimeEnd;

	sf::RectangleShape progress(sf::Vector2f(0, progressHeight));

	if (!font.loadFromFile("verdanab.ttf")){
		std::cerr << "Error loading verdanab.ttf" << std::endl;
	}

	changeMainMusic("game.ogg");

	//setBgTexture("bgMoon.jpg");
	sf::Texture bgTexture;
	bgTexture.loadFromFile("bgMoon.jpg");
	mainBg.setTexture(bgTexture);
	
	waveText.setFont(font);
	waveText.setCharacterSize(20);
	waveText.setString(getWaveText(waveCount, waves));
	waveText.setColor(getColor("default"));
	waveText.setPosition({ progressWidth + 30.f, progressHeight / 2.f});

	lifeText.setFont(font);
	lifeText.setCharacterSize(20);
	lifeText.setString(getLiveText(life));
	lifeText.setColor(getColor("default"));
	lifeText.setPosition({ 400.f, progressHeight / 2.f });

	goldText.setFont(font);
	goldText.setCharacterSize(20);
	goldText.setString(getGoldText(gold));
	goldText.setColor(getColor("default"));
	goldText.setPosition({ 600.f, progressHeight / 2.f });

	txtTime.setFont(font);
	txtTime.setCharacterSize(20);
	txtTime.setString("00:00");
	txtTime.setColor(getColor("default"));
	txtTime.setPosition({ 800.f, progressHeight / 2.f });

	sf::Text gameOver;
	gameOver.setFont(font);
	gameOver.setCharacterSize(64);
	gameOver.setString("Game Over");
	gameOver.setColor(sf::Color::Transparent);
	setTextCenter(gameOver, SCREENHEIGHT / 2.f);

	

	sf::RectangleShape gameOverMask(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	gameOverMask.setFillColor(sf::Color::Transparent);
	
	float towerIconWidth = 48.f;
	for (int i = 0; i < towers; i++){
		sf::RectangleShape* tower = new sf::RectangleShape(sf::Vector2f(towerIconWidth, towerIconWidth));
		tower->setFillColor(sf::Color(250, 150, 100));
		sf::FloatRect rec = tower->getLocalBounds();
		tower->setOrigin(rec.width / 2, rec.height / 2);
		float pos = (float)i*towerIconWidth * 1.5 + rec.width / 2;
		tower->setPosition({ pos, SCREENHEIGHT - rec.height / 2 });
		tower->setOutlineThickness(2);
		tower->setOutlineColor(sf::Color::Transparent);
		towerIcons.push_back(tower);
	}

	karte = new Map("map.txt");
	
	pathCounter = 0;
	movingEnemy = 1;

	bool waveRunning = false;

	int selecteTower = -1;
	bool towerSelected = false;

	Position* fieldPos = 0;

	int clockHoverMilli;

	sf::Clock clockHover;
	sf::Time timeHover;

	sf::Clock fpsClock;
	initShapes();

	kills = 0;

	int fieldHoverd = false;
	bool isTowerSelected = false;

	Turm* newTower = new Turm();
	türme.push_back(newTower);
	newTower->setAttackSpeed(2);
	newTower->setAngriff(10);
	newTower->setRange(2);

	decreaseGold(0);
	karte->getPositionen()[3][4]->setBebaubar(false);
	newTower->spawn(karte->getPositionen()[3][4]);
	newTower->berechneRangeFelder(karte->getPositionen());
	while (Running)
	{
		clockTime = clock.getElapsedTime();
		
		seconds = std::round(clockTime.asSeconds());

		timeHover = clockHover.getElapsedTime();
		clockHoverMilli = timeHover.asMilliseconds();

		float fps = 1.f / fpsClock.getElapsedTime().asSeconds();
		std::cout << fps << "\n";
		fpsClock.restart();
		//std::cout << clockMilli % 100 << " | " << clockMilli << "\n";
		while (app.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Escape){
					return	0;
				}
			}

			if (Event.type == sf::Event::MouseMoved){
				//std::cout << clockMilli % 100 << " | " << clockMilli;
				if (!waveRunning){
					if (clockHoverMilli >= 100 && isTowerSelected){
						if (!fieldHoverd){
							fieldPos = onFieldHover(Event, karte, "move");
						}
						fieldHoverd = true;
						std::cout << "hover Field \n";
						clockHover.restart();
					}
					else {
						fieldHoverd = false;
					}
				}
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				
				if (!waveRunning){
					if (Event.mouseButton.button == sf::Mouse::Left)
					{
						if (isTowerSelected && fieldPos != 0){
							if (isGoldAvailable(0)){
								fieldPos->setBebaubar(false);
								karte->initWegfindung();
								if (karte->getPath().size() > 0)
								{
									newTower = new Turm();
									türme.push_back(newTower);
									newTower->setAngriff(10);
									newTower->setAttackSpeed(2);
									newTower->setRange(2);
									fieldPos->setBebaut(true);
									decreaseGold(0);

									newTower->spawn(fieldPos);
									newTower->berechneRangeFelder(karte->getPositionen());
									playSound("addTower");
								}
								else
									fieldPos->setBebaubar(true);
									playSound("money");
									karte->initWegfindung();
							}
							else {
								playSound("money");
							}
						}
					}
					else
					{
					
						if (fieldPos &&fieldPos->getBebaut())
						{
							//int size = türme.size();
							for (int i = 0; i < türme.size(); i++)
							{
								if (fieldPos->getXCord() == türme[i]->getPosition()->getXCord() &&
									fieldPos->getYCord() == türme[i]->getPosition()->getYCord())
								{
									delete türme[i];
									türme[i] = 0;
									türme.erase(türme.begin() + i);
									break;
								}
							}
							
							fieldPos->setBebaut(false);
							playSound("money");
							karte->initWegfindung();
						}
					}
				}

				int selecteTowerPrev = selecteTower;

				selecteTower = onButtonHover(Event, towerIcons, "press");

				if (selecteTowerPrev != selecteTower && selecteTowerPrev > 0 && selecteTower > 0){
					towerIcons[selecteTowerPrev]->setOutlineColor(sf::Color::Transparent);
				}
				if (selecteTower == selecteTowerPrev && selecteTower >= 0){
					towerIcons[selecteTower]->setOutlineColor(sf::Color::Transparent);
					selecteTower = -1;
					isTowerSelected = false;
				}
				else if (selecteTower >= 0){
					towerIcons[selecteTower]->setOutlineColor(getColor("hover"));
					isTowerSelected = true;
				}
			}
				else
				{
				}
		}

		//Clearing screen
		app.clear(sf::Color(0, 0, 0, 0));

		app.draw(mainBg);
		drawMap(&app);

		time = waveClock.getElapsedTime();
		milli = std::round(time.asMilliseconds());

		clockTime = clock.getElapsedTime();
		seconds = std::round(clockTime.asSeconds());
		
		if (!died()){
			txtTime.setString(getTimeText(seconds));
		}

		if (!waveRunning){
			if (timePrev != milli && !died()){
				timePrev = std::round(time.asMilliseconds());

				if (!wavesEnded){
					progress.setSize(sf::Vector2f(progressSteps*milli, progressHeight));
				}

				if (milli >= waveTimeEnd){
					spawnWave();
					waveRunning = true;
					fieldPos = 0;
					//decreaseGold(89);
				}
			}
		}
		
		if (gegner.size() > 0)
		{
			if (karte->getPath().size() != 0)
			{
				double moveTime = moveClock.getElapsedTime().asMilliseconds();
				double smoothTime = moveClock.getElapsedTime().asMilliseconds();
				for (int k = 0; k <= movingEnemy - 1; k++)
				{
					if (gegner[k]->getNextX())
						gegner[k]->setSmoothX(gegner[k]->getSmoothNegativ()*(POSGRÖßE *((gegner[0]->getSpeed()*smoothTime) / 1000)));
					else
						gegner[k]->setSmoothY(gegner[k]->getSmoothNegativ()*(POSGRÖßE *((gegner[0]->getSpeed()*smoothTime) / 1000)));
				}

				if (moveTime>=1/gegner[0]->getSpeed()*1000)
				{
					for (int k = 0; k <= movingEnemy-1; k++){
						
					
						if (gegner[k]->getPosition() != karte->getZielPosition())
						{
							gegner[k]->move(karte->getPath()[pathCounter - (k * 2)]);
							
							gegner[k]->setSmoothX(0);
							gegner[k]->setSmoothY(0);
						}
						if (gegner[k]->getPosition() == karte->getZielPosition()&&
							!gegner[k]->getTot())
						{
							gegner[k]->setTot(true);
							kills++;
							decreaseLife(1);
						}
						if (gegner[k]->getPosition() != karte->getZielPosition())
						{
							if (karte->getPath()[pathCounter - (k * 2) + 1]->getXCord() == gegner[k]->getPosition()->getXCord())
							{
								gegner[k]->setNextX(false);
								if (karte->getPath()[pathCounter - (k * 2) + 1]->getYCord() > gegner[k]->getPosition()->getYCord())
									gegner[k]->setSmoothNegativ(1);
								else
									gegner[k]->setSmoothNegativ(-1);
							}
							else
							{
								gegner[k]->setNextX(true);
								if (karte->getPath()[pathCounter - (k * 2) + 1]->getXCord() > gegner[k]->getPosition()->getXCord())
									gegner[k]->setSmoothNegativ(1);
								else
									gegner[k]->setSmoothNegativ(-1);
							}
						}
					}
					if (movingEnemy < gegner.size() && pathCounter % 2 == 0 && pathCounter != 0)
					{
						movingEnemy++;
					}
						pathCounter++;
					
					moveClock.restart();
				}
			}
		}
		else {
			if (waveRunning){
				waveClock.restart();
			}
			waveRunning = false;
		}

		drawTürme(&app);

		app.draw(progress);
		app.draw(waveText);
		app.draw(lifeText);
		app.draw(goldText);
		app.draw(txtTime);

		drawTowerIcons(&app);

		app.draw(gameOverMask);
		app.draw(gameOver);

		if (died()){
			gameOver.setColor(getColor("red"));
			gameOverMask.setFillColor(getColor("mask"));
			app.draw(gameOverMask);
			app.draw(gameOver);
		}

		if (gegner.size()>0)
			drawGegner(&app);

		if (fieldPos != 0 && !waveRunning){
			field->setPosition(fieldPos->getXCordReal(), fieldPos->getYCordReal() + headerHeight);
			
			if (fieldPos->getBebaubar()){
				field->setFillColor(getColor("placeable"));
			}
			else {
				field->setFillColor(getColor("notplaceable"));
			}

			app.draw(*field);
		}

		app.display();

		angreiffendeEinheiten;
		
		if (gegner.size() > 0){
			for (int k = 0; k < gegner.size(); k++)
			{
				angreiffendeEinheiten = gegner[k]->isInRange(&türme);
				if (angreiffendeEinheiten.size() > 0)
				{

					for (int j = 0; j < angreiffendeEinheiten.size(); j++)
					{
						int attackTime = angreiffendeEinheiten[j]->getAttackClock().getElapsedTime().asSeconds();

						if (attackTime >= angreiffendeEinheiten[j]->getAttackSpeed() && !gegner[k]->getTot())
						{
							if (angreiffendeEinheiten[j]->angriff(gegner[k]))
							{
								kills++;
							}
							angreiffendeEinheiten.erase(angreiffendeEinheiten.begin() + j);
						}

					}
				}
			}
		}
		if (kills == gegner.size()&& kills >0)
		{
			löscheToteEinheiten();
		}
	}

	löschePositionen();
	löscheShapes();
	delete karte;
	karte = 0;

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}

void screen_4::drawTowerIcons(sf::RenderWindow *app){
	for (int i = 0; i < towers; i++){
		app->draw(*towerIcons[i]);
	}
}

void screen_4::drawMap(sf::RenderWindow *app)
{
	for (int i = 0; i < karte->getPositionen().size(); i++)
	{
		for (int j = 0; j < karte->getPositionen()[i].size(); j++)
		{
			tempPos = karte->getPositionen()[i][j];
			field->setPosition(tempPos->getXCordReal(), tempPos->getYCordReal() + headerHeight);

			if (karte->getStartPosition() == karte->getPositionen()[i][j]){
				field->setFillColor(getColor("start"));
			}
			else if (karte->getZielPosition() == karte->getPositionen()[i][j]){
				field->setFillColor(getColor("goal"));
			}
			else
				field->setFillColor(sf::Color::Transparent);
			app->draw(*field);
		}
	}
}

void screen_4::drawGegner(sf::RenderWindow *app)
{
	for (int j = 0; j < gegner.size(); j++){
		if (!gegner[j]->getTot())
		{
			double prozent = (gegner[j]->getMaxLeben() / 100);
			double scale = (gegner[j]->getLeben() / prozent) / 100;
			double feldscale = (POSGRÖßE * (1 - scale)/2);
			enemy->setSize(sf::Vector2f(POSGRÖßE*scale, POSGRÖßE*scale));
			enemy->setPosition(gegner[j]->getPosition()->getXCordReal() + gegner[j]->getSmoothX() + feldscale, gegner[j]->getPosition()->getYCordReal() + headerHeight + gegner[j]->getSmoothY() + feldscale);
			enemy->setFillColor(sf::Color::Red);
			
			app->draw(*enemy);
		}
	}
}

void screen_4::drawTürme(sf::RenderWindow *app)
{
	for (int j = 0; j < türme.size(); j++){
		if (!türme[j]->getTot())
		{
			tower->setPosition(türme[j]->getPosition()->getXCordReal(), türme[j]->getPosition()->getYCordReal() + headerHeight);
			tower->setFillColor(sf::Color::Magenta);		
			app->draw(*tower);
		}
	}
}

void screen_4::löschePositionen()
{
	for (int i = 0; i < karte->getPositionen().size() - 1; i++)
	{
		for (int j = 0; j < karte->getPositionen()[i].size(); j++)
		{
			delete karte->getPositionen()[i][j];
			karte->getPositionen()[i][j] = 0;
		}
	}
}

void screen_4::löscheToteEinheiten(){
		
	//lösche gegner	
	int size = gegner.size();
	for (int i = 0; i < size; i++)
	{
		delete gegner[0];
		gegner[0] = 0;
		gegner.erase(gegner.begin());
	}
}

void screen_4::löscheAlleEinheiten(){
	//lösche türme
	int size = türme.size();
	for (int i = 0; i < türme.size(); i++)
	{
		delete türme[0];
		türme[0] = 0;
		türme.erase(türme.begin());
	}
	//lösche gegner	
	size = gegner.size();
	for (int i = 0; i < gegner.size(); i++)
	{
		delete gegner[0];
		gegner[0] = 0;
		gegner.erase(gegner.begin());
	}
}
void screen_4::initShapes()
{
	field = new sf::RectangleShape(sf::Vector2f(POSGRÖßE, POSGRÖßE));
	field->setFillColor(sf::Color::Transparent);
	field->setOutlineThickness(1);
	//sf::FloatRect rec = field->getLocalBounds();
	//field->setOrigin(rec.width / 2, rec.height / 2);
	field->setOutlineColor(getColor("default"));

	tower = new sf::RectangleShape(sf::Vector2f(POSGRÖßE, POSGRÖßE));
	enemy = new sf::RectangleShape(sf::Vector2f(POSGRÖßE, POSGRÖßE));
}

void screen_4::löscheShapes()
{
	delete field;
	delete tower;
	delete enemy;
	tempPos = 0;
}