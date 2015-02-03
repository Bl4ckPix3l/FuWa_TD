#include "BodenGegner.h"


BodenGegner::BodenGegner()
{
}
BodenGegner::~BodenGegner()
{
}
void BodenGegner::move(Position zielPosition)
{
	position.setXCord(zielPosition.getXCord());
	position.setYCord(zielPosition.getYCord());
}

