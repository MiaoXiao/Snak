#pragma once

#include "Entity.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <vector>
#include <iostream>
#include "Globals.h"

class TurnTile: public Entity
{
public:
	TurnTile(float x, float y, bool starting, int oneway, std::vector<ALLEGRO_BITMAP*> a)
		:starting(starting), oneway(oneway), a(a)
	{
		//Entity
		posBegin.x = x;
		posBegin.y = y;
		posEnd.x = x + BLOCKSIZE;
		posEnd.y = y + BLOCKSIZE;
		collidable = false;

		//Turn Tile
		arrow = NONE;

		sample = al_load_sample("sounds/click.wav");
		if (!sample) {
			std::cout << "click.wav did not load!" << std::endl;
		}

		if (oneway != -1)
		{
			arrow = oneway;
		}
	}
	//draw turn tile
	void updateTurnTile();
	//move to next arrow if turntile is clicked
	void checkClick(float mpos_x, float mpos_y);
	int size;
	int arrow;
private:
	std::vector<ALLEGRO_BITMAP*> a;
	ALLEGRO_SAMPLE *sample;
	bool starting;
	int oneway;
};

