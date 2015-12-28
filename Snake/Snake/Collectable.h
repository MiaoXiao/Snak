#pragma once
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include "Entity.h"
#include "Globals.h"

class Collectable: public Entity
{
public:
	Collectable(float x, float y, int type, ALLEGRO_BITMAP* image)
		:type(type), image(image), id(id)
	{
		//Entity
		posBegin.x = x;
		posBegin.y = y;
		posEnd.x = x + BLOCKSIZE;
		posEnd.y = y + BLOCKSIZE;
		collidable = false;

		switch (type)
		{
		case BRONZE:
			score = 10;
			break;
		case SILVER:
			score = 25;
			break;
		case GOLD:
			score = 50;
			break;
		case STAR:
			score = 100;
			break;
		}

		obtained = false;
	}
	void updateCollectable();
	bool obtained;
private:
	
	int id;
	int type;
	int score;
	ALLEGRO_BITMAP* image;
};

