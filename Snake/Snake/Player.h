#pragma once

#include "stdafx.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include <iostream>
#include <vector>
#include <algorithm>

#include "Entity.h"
#include "Collectable.h"
#include "TurnTile.h"
#include "Globals.h"
#include "Barrier.h"

//Instance of player
class Player: public Entity
{
public:
	//CONSTRUCTOR: spawn location, move speed, event queue
	Player(float moveSpeed, ALLEGRO_EVENT_QUEUE * eq)
		: moveSpeed(moveSpeed)
	{
		//Player
		dir = NONE;
		lastDir = NONE;
		event_queue = eq;
		isDead = false;
		//std::cout << tailBegin.x << std::endl;
	}
	//reset player pos
	void resetPos(float x1, float y1);
	//get player input
	void getInput(ALLEGRO_EVENT events);
	//update player position
	void updatePlayer();
	//check if collided with tail or wall
	void collideBarrier(std::vector<Barrier> walls);
	//check collided with turn tile
	void collideTurnTile(std::vector<TurnTile> t);
	//check collide with collectable
	std::vector<Collectable> collideCollectable(std::vector<Collectable> c);

	//whether player dies
	bool isDead;
	//direction of movement
	int dir;
	std::vector<Barrier> tailList;
private:
	float moveSpeed;
	//event queue
	ALLEGRO_EVENT_QUEUE *event_queue;

	//draw all tails currently
	void updateTail();
	Position tailBegin;
	Position tailEnd;
	int lastDir;
};