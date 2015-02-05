#include "Einheit.h"


Einheit::Einheit()
{
}

Einheit::~Einheit()
{
}

void Einheit::spawn(Position *spawnPos)
{
	Position test = *spawnPos;
	position = spawnPos;
}

void Einheit::berechneRangeFelder(std::vector<std::vector<Position*>> positionen)
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
std::vector<Einheit*> Einheit::isInRange(std::vector<Einheit*> *pEinheiten)
{
	std::vector<Einheit*> einheitenInRange;
	for (int i = 0; i < pEinheiten->size(); i++)
	{
		for (int j = 0; j < pEinheiten->at(i)->getInRange().size(); j++)
		{
			if (position->getXCord() == pEinheiten->at(i)->getInRange()[j]->getXCord() &&
				position->getYCord() == pEinheiten->at(i)->getInRange()[j]->getYCord())
			{
				einheitenInRange.push_back(pEinheiten->at(i));
			}
		}
	}
	return einheitenInRange;
}


void Einheit::angriff(Einheit *angriffsZiel)
{
	angriffsZiel->setLeben(angriffsZiel->getLeben() - angriffsWert);
}
Position *Einheit::getPosition()
{
	return position;
}
int Einheit::getRange()
{
	return range;
}
int Einheit::getLeben()
{
	return leben;
}
bool Einheit::getTot()
{
	return tot;
}
std::vector<Position*> Einheit::getInRange()
{
	return inRange;
}
void Einheit::setRange(int pRange)
{
	range = pRange;
}
void Einheit::setAngriff(int pAngriff)
{
	angriffsWert = pAngriff;
}
void Einheit::setLeben(int pLeben)
{
	leben = pLeben;
	if (leben <= 0)
	{
		setTot(true);
	}
}
void Einheit::setTot(bool pTot)
{
	tot = pTot;
}

