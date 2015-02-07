#include <iostream>
#include "cScreen.hpp"
#include "globals.hpp"
#include "screen_4.hpp"

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
	
	std::map<std::string, std::string>* currWave = dbWaves[waveCount];
	int enemyCount = toInt(getResultsValue(currWave, "enemyCount"));
	int enemyLife = toInt(getResultsValue(currWave, "hp"));
	int enemyAttack = toInt(getResultsValue(currWave, "attack"));
	std::string enemyShape = getResultsValue(currWave, "color");

	for (int i = 0; i < enemyCount; i++){
		BodenGegner *enemy = new BodenGegner();
		enemy->setLeben(enemyLife);
		//enemy->set(enemyLife);
		enemy->setColor(enemyShape);
		enemy->setAngriff(enemyAttack);
		enemy->spawn(karte->getStartPosition());
		gegner.push_back(enemy);
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
	sf::Text txtTime;
	sf::Clock clock;

	sf::Time time;
	sf::Time clockTime;

	bool Running = true;
	
	float progressWidth = 120;
	float progressHeight = 50;
	float progressSteps = progressWidth / waveTimeEnd;

	sf::RectangleShape progress(sf::Vector2f(0, progressHeight));

	Model *model = new Model();
	dbTowers = model->getTowers();
	dbWaves = model->getWaves();

	waves = dbWaves.size();

	cScreen::isPlaying = true;

	changeMainMusic("sounds/game.ogg");

	sf::Texture bgTexture;
	bgTexture.loadFromFile(selectedMap[0]["image"]);
	mainBg.setTexture(bgTexture);
	
	waveText.setFont(*getMainFont());
	waveText.setCharacterSize(20);
	waveText.setString(getWaveText(waveCount, waves));
	waveText.setColor(getColor("default"));
	waveText.setPosition({ progressWidth + 30.f, progressHeight / 2.f});

	lifeText.setFont(*getMainFont());
	lifeText.setCharacterSize(20);
	lifeText.setString(getLiveText(life));
	lifeText.setColor(getColor("default"));
	lifeText.setPosition({ 400.f, progressHeight / 2.f });

	goldText.setFont(*getMainFont());
	goldText.setCharacterSize(20);
	goldText.setString(getGoldText(gold));
	goldText.setColor(getColor("default"));
	goldText.setPosition({ 600.f, progressHeight / 2.f });

	txtTime.setFont(*getMainFont());
	txtTime.setCharacterSize(20);
	txtTime.setString("00:00");
	txtTime.setColor(getColor("default"));
	txtTime.setPosition({ 800.f, progressHeight / 2.f });

	sf::Text gameOver;
	gameOver.setFont(*getMainFont());
	gameOver.setCharacterSize(64);
	gameOver.setString("Game Over");
	gameOver.setColor(sf::Color::Transparent);
	setTextCenter(gameOver, SCREENHEIGHT / 2.f);

	sf::RectangleShape gameOverMask(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	gameOverMask.setFillColor(sf::Color::Transparent);
	
	float towerIconWidth = 32.f;
	for (int i = 0; i < dbTowers.size(); i++){
		std::map<std::string, std::string>* entry = dbTowers[i];
		std::string name;
		std::string color;
		int shape;
		for (std::map<std::string, std::string>::iterator it = entry->begin(); it != entry->end(); ++it) {
			if (it->first == "name"){
				name = it->second;
			}
			else if (it->first == "shape"){
				shape = toInt(it->second);
			}
			else if (it->first == "color"){
				color = it->second;
			}
		}

		sf::CircleShape* tower = new sf::CircleShape(towerIconWidth, shape);
		tower->setFillColor(getColor(color));
		sf::FloatRect rec = tower->getLocalBounds();
		tower->setOrigin(rec.width / 2, rec.height / 2);
		float pos = (float)i*towerIconWidth * 2 + rec.width / 2;
		tower->setPosition({ pos, SCREENHEIGHT - rec.height / 2 });
		tower->setOutlineThickness(2);
		tower->setOutlineColor(sf::Color::Transparent);
		towerIcons.push_back(tower);
	}

	karte = new Map(selectedMap[0]["mappath"].c_str());
	
	int i = 0;
	int movingEnemy = 0;
	bool waveRunning = false;

	int selecteTower = -1;
	bool towerSelected = false;

	Position* fieldPos = 0;

	int clockHoverMilli;

	sf::Clock clockHover;
	sf::Time timeHover;

	sf::Clock fpsClock;
	initShapes();

	int fieldHoverd = false;
	bool isTowerSelected = false;

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
					if (fieldPos != 0 && !fieldPos->getBebaubar()){
						playSound("notable");
					}
					if (isTowerSelected && fieldPos != 0 && fieldPos->getBebaubar()){
						
						int cost = toInt(getResultsValue(dbTower, "cost"));
						if (isGoldAvailable(cost)){
							Turm* newTower = new Turm();
							türme.push_back(newTower);
							newTower->setAngriff(10);
							newTower->setRange(2);

							int shape = toInt(getResultsValue(dbTower, "shape"));
							int damage = toInt(getResultsValue(dbTower, "damage"));
							int range = toInt(getResultsValue(dbTower, "range"));
							std::string color = getResultsValue(dbTower, "color");
							
							newTower->setShape(shape);
							newTower->setAngriff(damage);
							newTower->setRange(range);
							newTower->setColor(color);

							decreaseGold(cost);
							fieldPos->setBebaubar(false);
							newTower->spawn(fieldPos);
							newTower->berechneRangeFelder(karte->getPositionen());
							playSound("addTower");
						}
						else {
							playSound("money");
						}
					}
					
				}

				int selecteTowerPrev = selecteTower;
				//selecteTower = onButtonHover(Event, towerIcons, "press");

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
					dbTower = dbTowers[selecteTower];
					isTowerSelected = true;
				}
				
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
					i = 0;
					spawnWave();
					karte->initWegfindung();
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
				for (int k = 0; k <= movingEnemy-1; k++){
					gegner[k]->move(karte->getPath()[i-k]);
					if (gegner[k]->getPosition() == karte->getZielPosition())
					{
						gegner[k]->setTot(true);
						decreaseLife(gegner[k]->getAngriff());
						löscheToteEinheiten();
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

		drawTowerIcons(&app);

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
						//angreiffendeEinheiten[j]->angriff(gegner[k]);
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
			else if (!tempPos->getBebaubar()){
				field->setFillColor(getColor("obstacle"));
			}
			else {
				field->setFillColor(sf::Color::Transparent);
			}
				
			app->draw(*field);
		}
	}
}

void screen_4::drawGegner(sf::RenderWindow *app)
{
	for (int j = 0; j < gegner.size(); j++){
		
		enemy->setPosition(gegner[j]->getPosition()->getXCordReal(), gegner[j]->getPosition()->getYCordReal() + headerHeight);
		enemy->setFillColor(sf::Color::Red);

		enemy->setFillColor(getColor(gegner[j]->getColor()));

		app->draw(*enemy);
	}
}

void screen_4::drawTürme(sf::RenderWindow *app)
{
	for (int j = 0; j < türme.size(); j++){
		tower->setPosition(türme[j]->getPosition()->getXCordReal(), türme[j]->getPosition()->getYCordReal() + headerHeight);
		tower->setFillColor(sf::Color::Magenta);
		
		
		tower->setPointCount(türme[j]->getShape());
		tower->setFillColor(getColor(türme[j]->getColor()));

		app->draw(*tower);
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
	//lösche türme
	if (türme.size() > 0){
		for (int i = 0; i < türme.size() - 1; i++)
		{
			if (türme[i]->getTot())
			{
				delete türme[i];
				türme[i] = 0;
				türme.erase(türme.begin() + i);
			}
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
void screen_4::initShapes()
{
	field = new sf::RectangleShape(sf::Vector2f(POSGRÖßE, POSGRÖßE));
	field->setFillColor(sf::Color::Transparent);
	field->setOutlineThickness(1);
	//sf::FloatRect rec = field->getLocalBounds();
	//field->setOrigin(rec.width / 2, rec.height / 2);
	field->setOutlineColor(getColor("default"));

	tower = new sf::CircleShape(POSGRÖßE/2, 3);
	enemy = new sf::RectangleShape(sf::Vector2f(POSGRÖßE, POSGRÖßE));
}

std::string screen_4::getResultsValue(std::map<std::string, std::string>* map, std::string name){
	for (std::map<std::string, std::string>::iterator it = map->begin(); it != map->end(); ++it) {
		if (it->first == name){
			return it->second;
		}
	}
}