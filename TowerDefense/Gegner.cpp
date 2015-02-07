#include "Gegner.h"

Gegner::Gegner()
{

}

Gegner::~Gegner()
{
}

std::vector<Turm*> Gegner::isInRange(std::vector<Turm*> *pTürme)
{
	std::vector<Turm*> einheitenInRange;
	for (int i = 0; i < pTürme->size(); i++)
	{
		for (int j = 0; j < pTürme->at(i)->getInRange().size(); j++)
		{
			if (position->getXCord() == pTürme->at(i)->getInRange()[j]->getXCord() &&
				position->getYCord() == pTürme->at(i)->getInRange()[j]->getYCord())
			{
				einheitenInRange.push_back(pTürme->at(i));
			}
		}
	}
	return einheitenInRange;
}

int Gegner::getSmoothX(){
	return smoothX;
}
int Gegner::getSmoothY(){
	return smoothY;
}
int Gegner::getSmoothNegativ(){
	return smoothNegativ;
}
bool Gegner::getNextX(){
	return nextX;
}
void Gegner::setSmoothX(int pSmoothX){
	smoothX = pSmoothX;
}
void Gegner::setSmoothNegativ(int pSmoothNegativ){
	smoothNegativ = pSmoothNegativ;
}
void Gegner::setSmoothY(int pSmoothY){
	smoothY = pSmoothY;
}
void Gegner::setNextX(bool pNextX){
	nextX = pNextX;
}