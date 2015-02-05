#include "Spiel.h"

#define POSGR��E 32

Spiel::Spiel()
{
}
Spiel::~Spiel()
{
}

void Spiel::run()
{
	karte = new Map("map.txt");
	//karte = *m1;
	gegner1.spawn(karte->getStartPosition());
	turm1.setRange(2);
	Position *test =karte->getPositionen().at(5)[7];
	Position *test2 = karte->getStartPosition();
	turm1.spawn(karte->getPositionen()[5][7]);
	turm1.berechneRangeFelder(karte->getPositionen());
	t�rme.push_back(turm1);

	drawAll();

	l�schePositionen();
	delete karte;
	karte = 0;
}
void Spiel::drawMap()
{
	for (int i = 0; i < karte->getPositionen().size(); i++)
	{
		for (int j = 0; j < karte->getPositionen()[i].size(); j++)
		{
			Position *tempPos = karte->getPositionen()[i][j];
			feldSprite.setPosition(tempPos->getXCord() * POSGR��E, tempPos->getYCord() * POSGR��E);
			sf::Texture tex;
			if (tempPos->getBebaubar())
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
	gegnerSprite.setPosition(gegner1.getPosition()->getXCord() * POSGR��E, gegner1.getPosition()->getYCord() * POSGR��E);
	sf::Texture tex;
	tex.loadFromFile("gegner.png");
	gegnerSprite.setTexture(tex);
	window->draw(gegnerSprite);

}

void Spiel::drawT�rme()
{
	turmSprite.setPosition(turm1.getPosition()->getXCord() * POSGR��E, turm1.getPosition()->getYCord() * POSGR��E);
	sf::Texture tex;
	tex.loadFromFile("turm.png");
	turmSprite.setTexture(tex);
	window->draw(turmSprite);
}
void Spiel::drawAll()
{
	window = new sf::RenderWindow(sf::VideoMode(POSGR��E* (karte->getPositionen()[0].size()), POSGR��E* (karte->getPositionen().size()), POSGR��E), "FuWA TD"); // style settings
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
		if (karte->getPath().size() != 0)
		{
			gegner1.move(karte->getPath()[i]);
		}
		std::vector<Einheit*> test = gegner1.isInRange(&t�rme);

		drawT�rme();
		drawGegner();
		window->display();

		if (gegner1.isInRange(&t�rme).size() > 0)
		{
			gegner1.spawn(karte->getPositionen()[0][0]);
			i = 0;
		}
		if (i < karte->getPath().size() - 1)
		{
			i++;
		}
	}
	delete window;
}
void Spiel::l�schePositionen()
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