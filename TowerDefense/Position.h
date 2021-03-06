#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Position
{
private:
	bool bebaubar;
	bool bebaut;
	int xCord;
	int yCord;
	int size;
	double berechneAbstand(Position *ziel);

	static int posSize;

	//wegfindung
	Position *vater;
	double entfernungStart =0;
	
	int status=0; // 0 = nicht bearbeitet (rot) 1 = in queue(gelb), 2 = bearbeitet(gr�n)

public:
	Position();
	~Position();
	void berechneWert(Position *ziel);
	bool getBebaubar();
	bool getBebaut();
	int getXCord();
	int getYCord();
	int getXCordReal();
	int getYCordReal();
	int getSize();
	double getWert();
	int getStatus();
	Position *getVater();
	double getEntfernungStart();
	void setBebaubar(bool pBebaubar);
	void setBebaut(bool pBebaut);
	void setXCord(int pXCord);
	void setYCord(int pYCord);
	void setSize(int pSize);
	void setWert(double pWert);
	void setStatus(int pStatus);
	void setEnfernungStart(double pEntfernungStart);
	void setVater(Position *pVater);
	double wert = 0;
};

