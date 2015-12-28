#include "stdafx.h"
#include "TurnTile.h"

using namespace std;

//draw turn tile
void TurnTile::updateTurnTile()
{
	//draw yellow border
	al_draw_rectangle(posBegin.x, posBegin.y, posEnd.x, posEnd.y,
		al_map_rgb(255, 255, 0),
		3.0);
	//draw arrow if applicable
	if (arrow != NONE)
	{
		switch (arrow)
		{
		case RIGHT: //display right arrow
			al_draw_bitmap(a[RIGHT], posBegin.x, posBegin.y, 0);
			break;
		case LEFT: //display left arrow
			al_draw_bitmap(a[LEFT], posBegin.x, posBegin.y, 0);
			break;
		case UP: //display up arrow
			al_draw_bitmap(a[UP], posBegin.x, posBegin.y, 0);
			break;
		case DOWN: //display down arrow
			al_draw_bitmap(a[DOWN], posBegin.x, posBegin.y, 0);
			break;
		}
	}
}

//move to next arrow if turntile is clicked
void TurnTile::checkClick(float mpos_x, float mpos_y)
{
	//cout << posBegin.x << " " << posBegin.y << endl;
	//cout << mpos_x << " " << mpos_y << endl;
	if (mpos_x > posBegin.x && mpos_x < posEnd.x &&
		mpos_y > posBegin.y && mpos_y < posEnd.y)
	{
		switch (arrow)
		{
		case UP: //display right arrow
			arrow = RIGHT;
			break;
		case DOWN: //display left arrow
			arrow = LEFT;
			break;
		case LEFT: //display up arrow
			arrow = UP;
			break;
		case RIGHT: //display down arrow
			arrow = DOWN;
			break;
		case NONE: // display up arrow
			arrow = UP;
			break;
		}
	}
}