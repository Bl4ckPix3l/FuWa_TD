#include <iostream>
#include "cScreen.hpp"
#include "screen_4.hpp"


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

void screen_4::spawnWave(){
	
	for (int i = 0; i < enemySpawn; i++){
		BodenGegner *enemy = new BodenGegner();
		enemy->setLeben(40);
		enemy->spawn(karte->getStartPosition());
		gegner.push_back(enemy);
	}

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


	//sf::vector

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

	sf::Text gameOver;
	gameOver.setFont(font);
	gameOver.setCharacterSize(64);
	gameOver.setString("Game Over");
	gameOver.setColor(sf::Color::Transparent);
	setTextCenter(gameOver, 756 / 2.f);
	//gameOver.setPosition({ 1024.f / 2.f, 756 / 2.f });

	//Spiel s;
	//s.run();

	karte = new Map("map.txt");
	//gegner1 = new BodenGegner();
	//gegner.push_back(gegner1);
	//gegner1->spawn(karte->getStartPosition());
	
	turm1 = new Turm();
	turm1->setAngriff(10);
	türme.push_back(turm1);
	turm1->setRange(2);

	turm1->spawn(karte->getPositionen()[5][7]);
	turm1->berechneRangeFelder(karte->getPositionen());

	int i = 0;
	int movingEnemy = 0;
	bool waveRunning = false;

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

		//Clearing screen
		app.clear(sf::Color(0, 0, 0, 0));

		drawMap(&app);

		sf::Time time = waveClock.getElapsedTime();
		sf::Time clockTime = clock.getElapsedTime();
		milli = std::round(time.asMilliseconds());
		seconds = std::round(clockTime.asSeconds());
		
		if (!died()){
			txtTime.setString(getTimeText(seconds));
		}
		else {
			gameOver.setColor(getColor("red"));
		}


		if (!waveRunning){
			if (timePrev != milli && !died()){
				timePrev = std::round(time.asMilliseconds());

				if (!wavesEnded){
					progress.setSize(sf::Vector2f(progressSteps*milli, progressHeight));
				}

				if (milli >= waveTimeEnd){
					i = 0;
					spawnWave();
					waveRunning = true;
					//gegner1->spawn(karte->getStartPosition());
					//i = 0;

					decreaseGold(89);
				}
			}
		}
		

		//app.draw(Rectangle);
		
		if (gegner.size() > 0)
		{
			if (karte->getPath().size() != 0)
			{
				for (int k = 0; k <= movingEnemy-1; k++){
					gegner[k]->move(karte->getPath()[i-k]);
					if (gegner[k]->getPosition() == karte->getZielPosition())
					{
						gegner[k]->setTot(true);
						löscheToteEinheiten();
						decreaseLife(20);
						movingEnemy--;
						i--;
					}
				}
				if (movingEnemy < gegner.size())
					movingEnemy ++;
				
			}
			if (i < karte->getPath().size() - 1 + gegner.size())
			{
				i++;
			}
		}
		else {
			if (waveRunning){
				waveClock.restart();
			}
			waveRunning = false;
			
		}
		//std::vector<Einheit*> test = gegner1.isInRange(&türme);

		drawTürme(&app);

		app.draw(progress);
		app.draw(waveText);
		app.draw(lifeText);
		app.draw(goldText);
		app.draw(txtTime);

		app.draw(gameOver);

		if (gegner.size()>0)
			drawGegner(&app);
		app.display();
		std::vector<Einheit*> angreiffendeEinheiten;
		if (gegner.size()>0)
			for (int k = 0; k < gegner.size(); k++)
			{
				angreiffendeEinheiten = gegner[k]->isInRange(&türme);
				if (angreiffendeEinheiten.size() > 0)
				{
					gegner[k]->spawn(karte->getPositionen()[0][0]);
					for (int j = 0; j < angreiffendeEinheiten.size(); j++)
					{
						angreiffendeEinheiten[j]->angriff(gegner[k]);
						löscheToteEinheiten();
					}

					//i = 0;
				}
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
			feldSprite.setPosition(tempPos->getXCord() * POSGRÖßE, tempPos->getYCord() * POSGRÖßE + headerHeight);
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
	for (int j = 0; j < gegner.size(); j++){
		gegnerSprite.setPosition(gegner[j]->getPosition()->getXCord() * POSGRÖßE, gegner[j]->getPosition()->getYCord() * POSGRÖßE + headerHeight);
		sf::Texture tex;
		tex.loadFromFile("gegner.png");
		gegnerSprite.setTexture(tex);
		app->draw(gegnerSprite);
	}
}

void screen_4::drawTürme(sf::RenderWindow *app)
{
	turmSprite.setPosition(turm1->getPosition()->getXCord() * POSGRÖßE, turm1->getPosition()->getYCord() * POSGRÖßE + headerHeight);
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

void screen_4::löscheToteEinheiten(){
	//lösche türme
	for (int i = 0; i < türme.size() - 1; i++)
	{
		if (türme[i]->getTot())
		{
			delete türme[i];
			türme[i] = 0;
			türme.erase(türme.begin() + i);
		}
	}
	//lösche gegner	
	for (int i = 0; i < gegner.size(); i++)
	{
		if (gegner[i]->getTot())
		{
			delete gegner[i];
			gegner[i] = 0;
			gegner.erase(gegner.begin()+i);
		}
	}
}

void screen_4::löscheAlleEinheiten(){
	//lösche türme
	for (int i = 0; i < türme.size() - 1; i++)
	{
		delete türme[i];
		türme[i] = 0;
		türme.erase(türme.begin() + i);
	}
	//lösche gegner	
	for (int i = 0; i < gegner.size() - 1; i++)
	{
		delete gegner[i];
		gegner[i] = 0;
		gegner.erase(gegner.begin() + i);
	}
}