#include "stdafx.h"
#include "Collectable.h"

using namespace std;

void Collectable::updateCollectable()
{
	//draw image
	al_draw_bitmap(image, posBegin.x, posBegin.y, 0);
}