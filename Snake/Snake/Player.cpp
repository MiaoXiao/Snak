#include "stdafx.h"
#include "Player.h"
using namespace std;

void Player::resetPos(float x1, float y1)
{
	posBegin.x = x1;
	posBegin.y = y1;
	posEnd.x = x1 + BLOCKSIZE;
	posEnd.y = y1 + BLOCKSIZE;

	tailBegin.x = posBegin.x;
	tailBegin.y = posBegin.y;
	tailEnd.x = posEnd.x;
	tailEnd.y = posEnd.y;

	dir = NONE;
	lastDir = NONE;
}

void Player::getInput(ALLEGRO_EVENT events)
{
	/*
	switch (events.keyboard.keycode)
	{
	case ALLEGRO_KEY_DOWN:
		dir = DOWN;
		break;
	case ALLEGRO_KEY_UP:
		dir = UP;
		break;
	case ALLEGRO_KEY_RIGHT:
		dir = RIGHT;
		break;
	case ALLEGRO_KEY_LEFT:
		dir = LEFT;
		break;
	}
	*/
}

//update player position
void Player::updatePlayer()
{
	if (!isDead && dir != NONE)
	{
		//if we are changing direction, get new tail beginning
		if (dir != lastDir)
		{
			//cout << "res tail" << endl;
			tailBegin.x = posBegin.x;
			tailBegin.y = posBegin.y;
			//cout << tailBegin.x << " " << tailBegin.y << endl;
		}

		//get next player position
		
		switch (dir)
		{
		case DOWN:
			posBegin.y += moveSpeed;
			posEnd.y += moveSpeed;
			break;
		case UP:
			posBegin.y -= moveSpeed;
			posEnd.y -= moveSpeed;
			break;
		case LEFT:
			posBegin.x -= moveSpeed;
			posEnd.x -= moveSpeed;
			break;
		case RIGHT:
			posBegin.x += moveSpeed;
			posEnd.x += moveSpeed;
			break;
		}
		
		//cout << posBegin.x << " " << posBegin.y << endl;
		//create new tail
		Barrier b;
		switch (dir)
		{
		case RIGHT:
			b.init(tailBegin.x, tailBegin.y + BLOCKSIZE / 2, posBegin.x, posBegin.y + BLOCKSIZE / 2);
			break;
		case LEFT:
			b.init(posBegin.x + BLOCKSIZE, posBegin.y + BLOCKSIZE / 2, tailBegin.x + BLOCKSIZE, tailBegin.y + BLOCKSIZE / 2);
			break;
		case UP:
			//cout << posBegin.x + BLOCKSIZE / 2 << " " << posBegin.y << " " << tailBegin.x + BLOCKSIZE / 2 << " " << tailBegin.y + BLOCKSIZE << endl;
			b.init(posBegin.x + BLOCKSIZE / 2, posBegin.y + BLOCKSIZE, tailBegin.x + BLOCKSIZE / 2, tailBegin.y + BLOCKSIZE);
			//cout << b.min.x << " " << b.min.y << " " << b.max.x << " " << b.max.y << endl;
			break;
		case DOWN:
			b.init(tailBegin.x + BLOCKSIZE / 2, tailBegin.y, posBegin.x + BLOCKSIZE / 2, posBegin.y);
			break;
		}

		//if moving in the same direction, overwrite last tail
		if (dir == lastDir && !tailList.empty()) tailList.pop_back();

		//push new tail, then update
		tailList.push_back(b);
	}
	//draw tail
	updateTail();

	//cout << "update p" << endl;
	//cout << posBegin.x << " " << posBegin.y << " " << posEnd.x << " " << posEnd.y << endl;
	//draw player
	al_draw_filled_rectangle(posBegin.x, posBegin.y, posEnd.x, posEnd.y,
		al_map_rgb(0, 0, 255));
	
	//update new direction
	lastDir = dir;
}

//draw all tails currently
void Player::updateTail()
{
	for (unsigned int i = 0; i < tailList.size(); ++i)
	{
		tailList[i].updateBarrier();
	}
}

//check if collided with tail or wall
void Player::collideBarrier(std::vector<Barrier> allBarriers)
{
	//cout << posBegin.x << " " << posBegin.y << " " << posEnd.x << " " << posEnd.y << endl;
	int wallSize = allBarriers.size();
	int loop;
	int direction;
	float a_max_x, a_max_y, a_min_x, a_min_y, b_max_x, b_max_y, b_min_x, b_min_y;
	if (!isDead && dir != NONE)
	{
		//cout << allBarriers.size() << endl;
		allBarriers.insert(allBarriers.end(), tailList.begin(), tailList.end());
		//check wall player to barrier collisions
		for (unsigned int i = 0; i < allBarriers.size() - 1; ++i)
		{
			direction = dir;
			/*
			cout << "i: " << i << endl;
			cout << posEnd.x << " > " << allBarriers[i].min.x << endl;
			cout << posBegin.x << " < " << allBarriers[i].max.x << endl;
			cout << posEnd.y << " > " << allBarriers[i].min.y << endl;
			cout << posBegin.y << " < " << allBarriers[i].max.y << endl;
			*/
			if (posEnd.x > allBarriers[i].min.x && posBegin.x < allBarriers[i].max.x &&
				posEnd.y > allBarriers[i].min.y && posBegin.y < allBarriers[i].max.y)
			{
				cout << "collide" << endl;
				isDead = true;
			}
			if (isDead)
			{
				//cout << "Loop: " << loop << endl;
				cout << "Direction: " << direction << endl;
				cout << "a.max.x " << posEnd.x << endl;
				cout << "a.max.y " << posEnd.y << endl;
				cout << endl;
				cout << "a.min.x " << posBegin.x << endl;
				cout << "a.min.y " << posBegin.y << endl;
				cout << endl;
				cout << "b.max.x " << allBarriers[i].max.x << endl;
				cout << "b.max.y " << allBarriers[i].max.y << endl;
				cout << endl;
				cout << "b.min.x " << allBarriers[i].min.x << endl;
				cout << "b.min.y " << allBarriers[i].min.y << endl;
				return;
				
			}
		}
	}
}

//check collided with turn tile
void Player::collideTurnTile(vector<TurnTile> t)
{
	for (unsigned int i = 0; i < t.size(); ++i)
	{
		//cout << posBegin.y << " " << t[i].posBegin.y << endl;
		if (t[i].arrow != NONE &&
			posBegin.x == t[i].posBegin.x &&
			posBegin.y == t[i].posBegin.y)
		{
			dir = t[i].arrow;
		}
	}

	//cout << posBegin.x << " " << posBegin.y << " " << posEnd.x << " " << posEnd.y << endl;
}

//check collided with collectable
vector<Collectable> Player::collideCollectable(vector<Collectable> c)
{
	
	for (unsigned int i = 0; i < c.size(); ++i)
	{
		if (posBegin.x == c[i].posBegin.x &&
			posBegin.y == c[i].posBegin.y)
		{
			cout << "obtained" << endl;
			c[i].obtained = true;
			c[i].playSound();
		}
	}
	return c;
}