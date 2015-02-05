#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Position
{
private:
	bool bebaubar;
	int xCord;
	int yCord;
	int size;
	double berechneAbstand(Position *ziel);

	//wegfindung
	Position *vater;
	double entfernungStart =0;
	
	int status=0; // 0 = nicht bearbeitet (rot) 1 = in queue(gelb), 2 = bearbeitet(grün)

public:
	Position();
	~Position();
	void berechneWert(Position *ziel);
	bool getBebaubar();
	int getXCord();
	int getYCord();
	int getSize();
	double getWert();
	int getStatus();
	Position *getVater();
	double getEntfernungStart();
	void setBebaubar(bool pBebaubar);
	void setXCord(int pXCord);
	void setYCord(int pYCord);
	void setSize(int pSize);
	void setWert(double pWert);
	void setStatus(int pStatus);
	void setEnfernungStart(double pEntfernungStart);
	void setVater(Position *pVater);
	double wert = 0;
};

