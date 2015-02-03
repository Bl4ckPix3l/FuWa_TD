#include "Spiel.h"

#define POSGRÖßE 32

Spiel::Spiel()
{
}
Spiel::~Spiel()
{
}

void Spiel::run()
{
	Map *m1 = new Map("map.txt");
	karte = *m1;
	gegner1.spawn(karte.getStartPosition());
	drawAll();
}
void Spiel::drawMap()
{
	for (int i = 0; i < karte.getPositionen().size(); i++)
	{
		for (int j = 0; j < karte.getPositionen()[i].size(); j++)
		{
			Position tempPos = karte.getPositionen()[i][j];
			feldSprite.setPosition(tempPos.getXCord() * POSGRÖßE, tempPos.getYCord() * POSGRÖßE);
			sf::Texture tex;
			if (tempPos.getBebaubar())
				tex.loadFromFile("bauplatz.png");
			else
				tex.loadFromFile("mauer.png");
			feldSprite.setTexture(tex);
			window->draw(feldSprite);
		}
	}
}

void Spiel::drawGegner()
{
	gegnerSprite.setPosition(gegner1.getPosition().getXCord() * POSGRÖßE, gegner1.getPosition().getYCord() * POSGRÖßE);
	sf::Texture tex;
	tex.loadFromFile("gegner.png");
	gegnerSprite.setTexture(tex);
	window->draw(gegnerSprite);
}
void Spiel::drawAll()
{
	window = new sf::RenderWindow(sf::VideoMode(POSGRÖßE* (karte.getPositionen()[0].size()), POSGRÖßE* (karte.getPositionen().size()), POSGRÖßE), "FuWA TD"); // style settings
	int i = 0;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			}
		}
		window->clear();

		drawMap();
		if (karte.getPath().size() != 0)
		{
			gegner1.move(karte.getPath()[i]);
		}
		
		if (i < karte.getPath().size()-1)
		{
			i++;
		}
		
		drawGegner();
		window->display();
	}
	delete window;
}