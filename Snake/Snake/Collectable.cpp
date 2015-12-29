#include "stdafx.h"
#include "Collectable.h"

using namespace std;

void Collectable::updateCollectable()
{
	//draw image
	al_draw_bitmap(image, posBegin.x, posBegin.y, 0);
}

void Collectable::playSound()
{
	al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}