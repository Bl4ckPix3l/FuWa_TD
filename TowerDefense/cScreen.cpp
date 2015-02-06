#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "cScreen.hpp"
#include "Position.h"
#include <string>
#include <vector>
#include <iostream>



sf::Music cScreen::music;
sf::Sprite cScreen::mainBg;
sf::Font cScreen::mainFont;
bool cScreen::isMusicOn;
int map;
int volk;


cScreen::cScreen(){
	sf::Texture Texture;

	buffer.loadFromFile("button.wav");
	sButton.setBuffer(buffer);

	cScreen::music.openFromFile("intro.ogg");

	cScreen::mainFont.loadFromFile("verdanab.ttf");

	initSounds();
	initColors();
}

sf::Font cScreen::getFont(){
	return mainFont;
}

void cScreen::initColors(){
	colors["default"] = new sf::Color(208, 181, 126);
	colors["red"] = new sf::Color(255, 0, 0, 255);
	colors["mask"] = new sf::Color(0, 0, 0, 100);
	colors["hover"] = new sf::Color(89, 230, 45);
	colors["start"] = new sf::Color(66, 234, 15, 80);
	colors["goal"] = new sf::Color(132, 10, 10, 80);
	colors["placeable"] = new sf::Color(255, 174, 0);
	colors["notplaceable"] = new sf::Color(229, 47, 47);
}

sf::Color cScreen::getColor(std::string name){
	return *colors[name];
}

sf::Sound* cScreen::createSound(std::string name){
	sf::Sound* soundX = new sf::Sound();
	sf::SoundBuffer* bufferX = new sf::SoundBuffer();
	bufferX->loadFromFile(name);
	soundX->setBuffer(*bufferX);
	return soundX;
}

void cScreen::initSounds(){
	sounds["lifeDec"] = createSound("lifeDec.wav");
	sounds["spawn1"] = createSound("spawn1.ogg");
	sounds["gameover"] = createSound("gameover.wav");
	sounds["money"] = createSound("money.wav");
	sounds["addTower"] = createSound("addTower.wav");
}

void cScreen::playSound(std::string type){
	sounds[type]->play();
}

sf::Texture cScreen::getBgTexture(){
	if (!Texture.loadFromFile(bgMain)){
		std::cerr << "Error Background menuMain.gif not found" << std::endl;
	}
	return Texture;
}

void cScreen::setBgTexture(std::string name){
	bgMain = name;
}

void cScreen::drawTexture(sf::RenderWindow *app){
	mainBg.setTexture(getBgTexture());
	app->draw(mainBg);
}

sf::Sprite cScreen::getMainBg(){
	return mainBg;
}

void cScreen::playMainMusic(){
	if (!isMusicOn){
		cScreen::music.play();
		isMusicOn = true;
	}

}

void cScreen::stopMainMusic(){
	if (isMusicOn){
		cScreen::music.stop();
		isMusicOn = false;
	}

}

void cScreen::changeMainMusic(std::string name){
	stopMainMusic();
	cScreen::music.openFromFile(name);
	playMainMusic();
}


void cScreen::setTextCenter(sf::Text &text, float yPosition){
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(sf::Vector2f(1024 / 2.0f, yPosition));
}

void cScreen::setSpriteCenter(sf::Sprite &sprite, float yPosition){
	sf::FloatRect textRect = sprite.getLocalBounds();
	sprite.setOrigin(textRect.width / 2, textRect.height / 2);
	sprite.setPosition(sf::Vector2f(1024 / 2.0f, yPosition));
}

void cScreen::setButtonCenter(sf::RectangleShape &rec, float yPosition){
	sf::FloatRect textRect = rec.getLocalBounds();
	rec.setOrigin(textRect.width / 2, textRect.height / 2);
	rec.setPosition(sf::Vector2f(1024 / 2.0f, yPosition));
}


int cScreen::onButtonHover(sf::Event Event, std::vector<sf::RectangleShape*>  menuListButton, std::string type){
	float posX, posY, btnWidth, btnHeight;
	float leftEdge, rightEdge, topEdge, bottomEdge;

	int moveX, moveY;

	bool btnEnterd = false;

	if (type == "move"){
		moveX = Event.mouseMove.x;
		moveY = Event.mouseMove.y;
	}
	else if (type == "press"){
		moveX = Event.mouseButton.x;
		moveY = Event.mouseButton.y;
	}
	else {
		return -1;
	}

	for (int i = 0; i < menuListButton.size(); i++){
	//for (std::vector<sf::RectangleShape>::iterator i = menuListButton.begin(); i != menuListButton.end(); ++i) {
		posX = menuListButton[i]->getPosition().x;
		posY = menuListButton[i]->getPosition().y;

		btnWidth = menuListButton[i]->getLocalBounds().width;
		btnHeight = menuListButton[i]->getLocalBounds().height;

		leftEdge = posX - btnWidth / 2;
		rightEdge = posX + btnWidth / 2;
		topEdge = posY - btnHeight / 2;
		bottomEdge = posY + btnHeight / 2;

		std::cout << "x:" << moveX << " y:" << moveY << "\n";

		if (moveX > leftEdge && moveX < rightEdge && moveY > topEdge && moveY < bottomEdge){
			std::cout << "button entered" << i << " \n";
			btnEnterd = true;

			return i;
		}

	}
	return -1;
}

Position* cScreen::onFieldHover(sf::Event Event, Map* karte, std::string type){
	float posX, posY, btnWidth, btnHeight;
	float leftEdge, rightEdge, topEdge, bottomEdge;

	int moveX, moveY;

	bool btnEnterd = false;

	if (type == "move"){
		moveX = Event.mouseMove.x;
		moveY = Event.mouseMove.y;
	}
	else if (type == "press"){
		moveX = Event.mouseButton.x;
		moveY = Event.mouseButton.y;
	}
	else {
		return 0;
	}

	Position *tempPos;
	for (int i = 0; i < karte->getPositionen().size(); i++)
	{
		for (int j = 0; j < karte->getPositionen()[i].size(); j++)
		{
			//for (std::vector<sf::RectangleShape>::iterator i = menuListButton.begin(); i != menuListButton.end(); ++i) {
			
			tempPos = karte->getPositionen()[i][j];
			posX = tempPos->getXCordReal()+32;
			posY = tempPos->getYCordReal()+96;

			btnWidth = 64;
			btnHeight = 64;

			leftEdge = posX - btnWidth / 2;
			rightEdge = posX + btnWidth / 2;
			topEdge = posY - btnHeight / 2;
			bottomEdge = posY + btnHeight / 2;

			//std::cout << "x:" << posX << " y:" << posY << " | ";

			if (moveX > leftEdge && moveX < rightEdge && moveY > topEdge && moveY < bottomEdge){
				btnEnterd = true;

				return tempPos;
			}
		}

	}
	return 0;
}



void cScreen::playButtonSound(){
	sButton.play();
}