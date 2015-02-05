#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "cScreen.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <map>


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

	/*if (!mainFont.loadFromFile("verdanab.ttf")){
		std::cerr << "Error loading verdanab.ttf" << std::endl;
	}*/

	initSounds();
	initColors();
}

sf::Font cScreen::getFont(){
	return mainFont;
}

void cScreen::initColors(){
	colors["default"] = new sf::Color(208, 181, 126);
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
}

void cScreen::playSound(std::string type){
	sounds[type]->play();
}

sf::Texture cScreen::getBgTexture(){
	sf::Texture Texture;
	if (!Texture.loadFromFile("menuMain.jpg")){
		std::cerr << "Error loading menuMain.gif" << std::endl;
	}
	return Texture;
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


int cScreen::onButtonHover(sf::Event Event, std::vector<sf::RectangleShape>  menuListButton, std::string type){
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

	int count = 0;
	for (std::vector<sf::RectangleShape>::iterator i = menuListButton.begin(); i != menuListButton.end(); ++i) {
		posX = i->getPosition().x;
		posY = i->getPosition().y;

		btnWidth = i->getLocalBounds().width;
		btnHeight = i->getLocalBounds().height;

		leftEdge = posX - btnWidth / 2;
		rightEdge = posX + btnWidth / 2;
		topEdge = posY - btnHeight / 2;
		bottomEdge = posY + btnHeight / 2;

		std::cout << "x:" << leftEdge << " y:" << topEdge << "\n";

		if (moveX > leftEdge && moveX < rightEdge && moveY > topEdge && moveY < bottomEdge){
			std::cout << "button entered" << count << " \n";
			/*if (menu != count){
			playButtonSound();
			}
			menu = count;
			*/
			btnEnterd = true;

			return count;
		}

		count++;
	}
	return -1;
}

void cScreen::playButtonSound(){
	sButton.play();
}