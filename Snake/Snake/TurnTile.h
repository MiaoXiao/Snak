#pragma once

#include "Entity.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include <vector>
#include <iostream>
#include "Globals.h"

class TurnTile: public Entity
{
public:
	TurnTile(float x, float y, std::vector<ALLEGRO_BITMAP*> a)
		:size(size), a(a)
	{
		//Entity
		posBegin.x = x;
		posBegin.y = y;
		posEnd.x = x + BLOCKSIZE;
		posEnd.y = y + BLOCKSIZE;
		collidable = false;

		//Turn Tile
		arrow = NONE;
	}
	//draw turn tile
	void updateTurnTile();
	//move to next arrow if turntile is clicked
	void checkClick(float mpos_x, float mpos_y);
	int size;
	int arrow;
private:
	std::vector<ALLEGRO_BITMAP*> a;
};

