#include <iostream>
#include "cScreen.hpp"
#include "screen_4.hpp"
#include "Spiel.h"

#define POSGRÖßE 32

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

void screen_4::spamWave(){
	increaseWave();
	playSound("spawn1");
	waveClock.restart();
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

	bool Running = true;
	
	float progressWidth = 120;
	float progressHeight = 50;
	float progressSteps = progressWidth / waveTimeEnd;

	sf::RectangleShape progress(sf::Vector2f(0, progressHeight));

	if (!font.loadFromFile("verdanab.ttf")){
		std::cerr << "Error loading verdanab.ttf" << std::endl;
	}
	
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

	//Spiel s;
	//s.run();

	karte = new Map("map.txt");
	//karte = *m1;
	gegner1.spawn(karte->getStartPosition());
	turm1.setRange(2);
	Position *test = karte->getPositionen().at(5)[7];
	Position *test2 = karte->getStartPosition();
	turm1.spawn(karte->getPositionen()[5][7]);
	turm1.berechneRangeFelder(karte->getPositionen());
	türme.push_back(turm1);

	

	int i = 0;

	while (Running)
	{
		//Verifying events
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

			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{

			}
		}

		sf::Time time = waveClock.getElapsedTime();
		sf::Time clockTime = clock.getElapsedTime();
		milli = std::round(time.asMilliseconds());
		seconds = std::round(clockTime.asSeconds());
		
		if (!died()){
			txtTime.setString(getTimeText(seconds));
		}

		if (timePrev != milli && !died()){
			timePrev = std::round(time.asMilliseconds());
			
			if (!wavesEnded){
				progress.setSize(sf::Vector2f(progressSteps*milli, progressHeight));
			}

			if (milli >= waveTimeEnd){
				spamWave();
				decreaseLife(11);
				decreaseGold(89);
			}
		}

		//Clearing screen
		app.clear(sf::Color(0, 0, 0, 0));

		app.draw(progress);
		app.draw(waveText);
		app.draw(lifeText);
		app.draw(goldText);
		app.draw(txtTime);

		//app.draw(Rectangle);

		drawMap(&app);
		if (karte->getPath().size() != 0)
		{
			gegner1.move(karte->getPath()[i]);
		}
		std::vector<Einheit*> test = gegner1.isInRange(&türme);

		drawTürme(&app);
		drawGegner(&app);
		app.display();

		if (gegner1.isInRange(&türme).size() > 0)
		{
			gegner1.spawn(karte->getPositionen()[0][0]);
			i = 0;
		}
		if (i < karte->getPath().size() - 1)
		{
			i++;
		}
	}

	löschePositionen();
	delete karte;
	karte = 0;

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}

void screen_4::drawMap(sf::RenderWindow *app)
{
	for (int i = 0; i < karte->getPositionen().size(); i++)
	{
		for (int j = 0; j < karte->getPositionen()[i].size(); j++)
		{
			Position *tempPos = karte->getPositionen()[i][j];
			feldSprite.setPosition(tempPos->getXCord() * POSGRÖßE, tempPos->getYCord() * POSGRÖßE);
			sf::Texture tex;
			if (tempPos->getBebaubar())
				tex.loadFromFile("bauplatz.png");
			else
				tex.loadFromFile("mauer.png");
			feldSprite.setTexture(tex);
			app->draw(feldSprite);
		}
	}
}

void screen_4::drawGegner(sf::RenderWindow *app)
{
	gegnerSprite.setPosition(gegner1.getPosition()->getXCord() * POSGRÖßE, gegner1.getPosition()->getYCord() * POSGRÖßE);
	sf::Texture tex;
	tex.loadFromFile("gegner.png");
	gegnerSprite.setTexture(tex);
	app->draw(gegnerSprite);

}

void screen_4::drawTürme(sf::RenderWindow *app)
{
	turmSprite.setPosition(turm1.getPosition()->getXCord() * POSGRÖßE, turm1.getPosition()->getYCord() * POSGRÖßE);
	sf::Texture tex;
	tex.loadFromFile("turm.png");
	turmSprite.setTexture(tex);
	app->draw(turmSprite);
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