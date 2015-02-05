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
Position *Einheit::getPosition()
{
	return position;
}
int Einheit::getRange()
{
	return range;
}
std::vector<Position*> Einheit::getInRange()
{
	return inRange;
}
void Einheit::setRange(int pRange)
{
	range = pRange;
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
					inRange.push_back(positionen[i][j]);
				}
			}
		}
	}
}
std::vector<Einheit*> Einheit::isInRange(std::vector<Einheit> *pEinheiten)
{
	std::vector<Einheit*> einheitenInRange;
	for (int i = 0; i < pEinheiten->size(); i++)
	{
		for (int j = 0; j < pEinheiten->at(i).getInRange().size(); j++)
		{
			if (position->getXCord() == pEinheiten->at(i).getInRange()[j]->getXCord() &&
				position->getYCord() == pEinheiten->at(i).getInRange()[j]->getYCord())
			{
				einheitenInRange.push_back(&pEinheiten->at(i));
			}
		}
	}
	return einheitenInRange;
}