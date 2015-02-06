#include "Map.h"

Map::Map(const char*filename)
{
	int x = 0;
	int y = 0;
	std::ifstream openfile(filename);
	positionen.clear();
	std::vector<Position*> row;
	

	if (openfile.is_open())
	{
		std::string feldLocation;
		openfile >> feldLocation;
		mauerTexture.loadFromFile(feldLocation);

		openfile >> feldLocation;
		bauplatzTexture.loadFromFile(feldLocation);

		while (!openfile.eof())
		{
			std::string str;
			openfile >> str;
			char  feldTyp = str[0];

			Position *pos = new Position();
			pos->setXCord(x);
			pos->setYCord(y);
			x++;

			switch (feldTyp)
			{
			case 'x':
				pos->setBebaubar(false);
				break;
			case 's':
				pos->setBebaubar(false);
				start = pos;
				break;
			case 'z':
				pos->setBebaubar(false);
				ziel = pos;
				break;
			case 'o':
				pos->setBebaubar(true);
				break;
			default:
				break;
			}
			
			row.push_back(pos);

			if (openfile.peek() == '\n')
			{
				positionen.push_back(row);
				row.clear();
				y++;
				x = 0;
			}
		}
		positionen.push_back(row);
	}
	initWegfindung();
}

Map::Map()
{
}
Map::~Map()
{
}

std::vector<std::vector<Position *>> Map::getPositionen()
{
	return positionen;
}

int Map::getBreite()
{
	return positionen[0].size();
}
int Map::getHöhe(){
	return positionen.size();
}

Position * Map::getStartPosition()
{
	return start;
}
Position * Map::getZielPosition()
{
	return ziel;
}

std::vector<Position*> Map::getPath()
{
	return path;
}

void  Map::berechneWeg()
{
	for (int i = 0; queue.size() !=0 ; i++)
	{
		Position *aktPos = queue[0];
		Position *ptrAktPos = positionen[aktPos->getYCord()][aktPos->getXCord()];
		positionen[aktPos->getYCord()][aktPos->getXCord()]->setStatus(2);
		queue.erase(queue.begin());
		if (aktPos->getXCord() == ziel->getXCord() && aktPos->getYCord() == ziel->getYCord())
		{
			path.insert(path.begin(), aktPos);
			break;
		}
		//oben
		if (aktPos->getYCord() > 0 &&
			positionen[aktPos->getYCord() - 1][aktPos->getXCord()]->getStatus() == 0 &&
			(positionen[aktPos->getYCord() - 1][aktPos->getXCord()]->getBebaubar() ||
			positionen[aktPos->getYCord() - 1][aktPos->getXCord()]->getXCord() == ziel->getXCord() &&
			positionen[aktPos->getYCord() - 1][aktPos->getXCord()]->getYCord() == ziel->getYCord()))
		{
			addNachbar(positionen[aktPos->getYCord() - 1][aktPos->getXCord()], ptrAktPos);
		}
		//links
		if (aktPos->getXCord() > 0 &&
			positionen[aktPos->getYCord()][aktPos->getXCord() - 1]->getStatus() == 0 &&
			(positionen[aktPos->getYCord()][aktPos->getXCord() - 1]->getBebaubar() ||
			positionen[aktPos->getYCord()][aktPos->getXCord() - 1]->getXCord() == ziel->getXCord() &&
			positionen[aktPos->getYCord()][aktPos->getXCord() - 1]->getYCord() == ziel->getYCord()))
		{
			addNachbar(positionen[aktPos->getYCord()][aktPos->getXCord() - 1], ptrAktPos);
		}
		//rechts
		if (aktPos->getXCord() < positionen[0].size() - 1 &&
			positionen[aktPos->getYCord()][aktPos->getXCord() + 1]->getStatus() == 0 &&
			(positionen[aktPos->getYCord()][aktPos->getXCord() + 1]->getBebaubar() ||
			positionen[aktPos->getYCord()][aktPos->getXCord() + 1]->getXCord() == ziel->getXCord() &&
			positionen[aktPos->getYCord()][aktPos->getXCord() + 1]->getYCord() == ziel->getYCord()))
		{
			addNachbar(positionen[aktPos->getYCord()][aktPos->getXCord() + 1], ptrAktPos);
		}
		//unten
		if (aktPos->getYCord() < positionen.size() - 1 &&
			positionen[aktPos->getYCord() + 1][aktPos->getXCord()]->getStatus() == 0 &&
			(positionen[aktPos->getYCord() + 1][aktPos->getXCord()]->getBebaubar() ||
			positionen[aktPos->getYCord() + 1][aktPos->getXCord()]->getXCord() == ziel->getXCord() &&
			positionen[aktPos->getYCord() + 1][aktPos->getXCord()]->getYCord() == ziel->getYCord()))
		{ 
			addNachbar(positionen[aktPos->getYCord() + 1][aktPos->getXCord()], ptrAktPos);
		}
		sortiereVector();
	}

	if (path.size() != 0)
	{
		while (path[0]->getXCord() != start->getXCord() || path[0]->getYCord() != start->getYCord())
		{
			path.insert(path.begin(), path[0]->getVater());
		}
	}
}

void Map::sortiereVector()
{
	int i, j;
	for (i = 0; i < queue.size() - 1; ++i)
	{

		for (j = 0; j < queue.size() - i - 1; ++j)
		{
			if (queue[j]->getWert() > queue[j + 1]->getWert())
			{
				Position *tmp = queue[j];
				queue[j] = queue[j + 1];
				queue[j + 1] = tmp;
			}
		}
	}
}

void Map::addNachbar(Position *pos, Position *pVater)
{
	pos->setVater(pVater);
	pos->setStatus(1);
	pos->berechneWert(ziel);
	queue.push_back(pos);
}

void  Map::initWegfindung()
{	
	for (int i = 0; i < positionen.size(); i++)
	{
		for (int j = 0; j < positionen[0].size(); j++)
		{
			positionen[i][j]->setStatus(0);
		}
	}
	start->setEnfernungStart(0);
	start->setWert(sqrt(pow(ziel->getXCord() - start->getXCord(), 2) + pow(ziel->getYCord() - start->getYCord(), 2)));
	start->setStatus(1);
	queue.push_back(start);
	berechneWeg();
}


