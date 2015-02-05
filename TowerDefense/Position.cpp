#include "Position.h"


Position::Position()
{
	setStatus(0);
}
Position::~Position()
{
}

void Position::berechneWert(Position *ziel)
{
	entfernungStart = vater->getEntfernungStart() + 1;
	double test = vater->getEntfernungStart();
	wert = berechneAbstand(ziel) + entfernungStart;
}

double Position::berechneAbstand(Position *ziel)
{
	double ergebnis = sqrt(pow(ziel->getXCord() - xCord, 2) + pow(ziel->getYCord() - yCord, 2));
	return ergebnis;
}

bool Position::getBebaubar()
{
	return bebaubar;
}
int Position::getXCord()
{
	return xCord;
}
int Position::getYCord()
{
	return yCord;
}
int Position::getSize()
{
	return size;
}
double Position::getWert()
{
	return wert;
}
int Position::getStatus()
{
	return status;
}

double Position::getEntfernungStart()
{
	return entfernungStart;
}
Position *Position::getVater()
{
	return vater;
}
void Position::setBebaubar(bool pBebaubar)
{
	bebaubar = pBebaubar;
}
void Position::setXCord(int pXCord)
{
	xCord = pXCord;
}
void Position::setYCord(int pYCord)
{
	yCord = pYCord;
}
void Position::setSize(int pSize)
{
	size = pSize;
}
void Position::setWert(double pWert)
{
	wert = pWert;
}
void Position::setStatus(int pStatus)
{
	status = pStatus;
}
void Position::setEnfernungStart(double pEnfernungStart)
{
	entfernungStart = pEnfernungStart;
}
void Position::setVater(Position *pVater)
{
	vater = pVater;
}