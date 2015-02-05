#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class screen_4 : public cScreen
{
private:
	int waves = 30;
	int waveCount = 0;
	int waveTimeEnd = 1500;

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

public:
	screen_4(void);
	virtual int Run(sf::RenderWindow &App);
	std::string getWaveText(int count, int max);
	std::string getLiveText(int count);
	std::string getGoldText(int count);
	std::string getTimeText(int seconds);
	void increaseWave();
	bool checkWaveSpaming();
	void spamWave();
	void decreaseLife(int count);
	bool died();
	void increaseGold(int value);
	void decreaseGold(int value);
	bool isGoldAvailable(int value);
};

/*
screen_4::screen_4(void)
{

}

int screen_4::Run(sf::RenderWindow &App)
{
	sf::Event Event;



	bool Running = true;

	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
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
		App.clear(sf::Color(0, 0, 0, 0));


		//App.draw(Rectangle);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}*/