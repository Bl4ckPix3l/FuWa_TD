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

void Einheit::setRange(int pRange)
{
	range = pRange;
}
void Einheit::setAngriff(int pAngriff)
{
	angriffsWert = pAngriff;
}

double Einheit::getAngriff()
{
	return angriffsWert;
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


void Einheit::setShape(int pShape){
	shape = pShape;
}

int Einheit::getShape(){
	return shape;
}

void Einheit::setColor(std::string pColor){
	color = pColor;
}

std::string Einheit::getColor(){
	return color;
}

void Einheit::setSpeed(double pSpeed)
{
	speed = pSpeed;
}

