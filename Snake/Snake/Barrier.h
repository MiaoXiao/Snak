#pragma once

#include "Entity.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include <iostream>
#include "Globals.h"

class Barrier: public Entity
{
public:
	Barrier()
	{
		collidable = false;
	}
	Barrier(float x1, float y1, float x2, float y2)
	{
		init(x1, y1, x2, y2);
		if (x1 == x2)
		{
			min.y = y1;
			max.y = y2;
			min.x = x1 - BLOCKSIZE / 2;
			max.x = x2 + BLOCKSIZE / 2;
			//std::cout << min.x << " " << min.y << " " << max.x << " " << max.y << std::endl;
		}
		else if (y1 == y2)
		{
			min.x = x1;
			max.x = x2;
			min.y = y1 - BLOCKSIZE / 2;
			max.y = y2 + BLOCKSIZE / 2;
		}
		else
		{
			std::cout << "Invalid barrier" << std::endl;
		}
		collidable = false;
	}
	void init(float x1, float y1, float x2, float y2);
	void updateBarrier();
	Position min;
	Position max;
private:
};

