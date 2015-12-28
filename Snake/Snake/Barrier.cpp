#include "stdafx.h"
#include "Barrier.h"

using namespace std;

void Barrier::init(float x1, float y1, float x2, float y2)
{
	posBegin.x = x1;
	posBegin.y = y1;
	posEnd.x = x2;
	posEnd.y = y2;

	if (x1 == x2)
	{
		min.y = y1;
		max.y = y2;
		min.x = x1 - BLOCKSIZE / 2;
		max.x = x2 + BLOCKSIZE / 2;
		std::cout << min.x << " " << min.y << " " << max.x << " " << max.y << std::endl;
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
}

void Barrier::updateBarrier()
{
	al_draw_line(posBegin.x, posBegin.y, posEnd.x, posEnd.y,
		al_map_rgb(0, 0, 0),
		BLOCKSIZE);
}
