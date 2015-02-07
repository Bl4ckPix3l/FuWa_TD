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

double Einheit::getLeben()
{
	return leben;
}
double Einheit::getMaxLeben()
{
	return maxLeben;
}
bool Einheit::getTot()
{
	return tot;
}
double Einheit::getSpeed()
{
	return speed;
}

bool Einheit::setLeben(double pLeben)
{
	leben = pLeben;
	if (leben <= 0)
	{
		setTot(true);
		return true;
	}
	return false;
}
void Einheit::setMaxLeben(double pMaxLeben)
{
	maxLeben = pMaxLeben;
}
void Einheit::setTot(bool pTot)
{
	tot = pTot;
}

void Einheit::setSpeed(double pSpeed)
{
	speed = pSpeed;
}
