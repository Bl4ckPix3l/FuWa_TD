#include "Gegner.h"

Gegner::Gegner()
{

}

Gegner::~Gegner()
{
}

std::vector<Turm*> Gegner::isInRange(std::vector<Turm*> *pT�rme)
{
	std::vector<Turm*> einheitenInRange;
	for (int i = 0; i < pT�rme->size(); i++)
	{
		for (int j = 0; j < pT�rme->at(i)->getInRange().size(); j++)
		{
			if (position->getXCord() == pT�rme->at(i)->getInRange()[j]->getXCord() &&
				position->getYCord() == pT�rme->at(i)->getInRange()[j]->getYCord())
			{
				einheitenInRange.push_back(pT�rme->at(i));
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