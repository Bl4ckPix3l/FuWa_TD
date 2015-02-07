#include "Turm.h"


Turm::Turm()
{
}


Turm::~Turm()
{
}
bool Turm::angriff(Einheit *angriffsZiel)
{
	bool kill;
	kill = angriffsZiel->setLeben(angriffsZiel->getLeben() - angriffsWert);
	attackClock.restart();
	return kill;
}

int Turm::getRange()
{
	return range;
}
std::vector<Position*> Turm::getInRange()
{
	return inRange;
}
sf::Clock Turm::getAttackClock()
{
	return attackClock;
}
int Turm::getAttackSpeed()
{
	return attackSpeed;
}
void Turm::setRange(int pRange)
{
	range = pRange;
}
void Turm::setAngriff(int pAngriff)
{
	angriffsWert = pAngriff;
}
void Turm::setAttackSpeed(int pAttackSpeed)
{
	attackSpeed = pAttackSpeed;
}
void Turm::berechneRangeFelder(std::vector<std::vector<Position*>> positionen)
{
	inRange.clear();
	for (int i = 0; i < positionen.size() - 1; i++)
	{
		for (int j = 0; j < positionen[i].size() - 1; j++)
		{
			int px = positionen[i][j]->getXCord();
			int py = positionen[i][j]->getYCord();
			if (px > position->getXCord() - range && px < position->getXCord() + range)
			{
				if (py > position->getYCord() - range && py < position->getYCord() + range)
				{
					if (px != position->getXCord() || py != position->getYCord())
					{
						inRange.push_back(positionen[i][j]);
					}
				}
			}
		}
	}
}