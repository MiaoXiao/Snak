#pragma once

#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Entity.h"
#include "Player.h"
#include "Globals.h"
#include "Barrier.h"
#include "TurnTile.h"
#include "Collectable.h"

struct Score
{
	int totalPoints;
	std::vector<int> levelPoints;
	int starsLeft;
	int bronze;
	int silver;
	int gold;
};

struct Tile
{
	Tile()
	{
		int i = 0;
		for (unsigned int y = 0; y <= SCREENHEIGHT; y += TILEHEIGHT)
		{
			//std::cout << "inc" << std::endl;
			std::vector<Position> subp;
			pos.push_back(subp);

			Position p;
			p.y = y;
			for (unsigned int x = 0; x <= SCREENWIDTH; x += TILEWIDTH)
			{
				p.x = x;
				pos[i].push_back(p);
			}
			i++;

		}
		/*
		for (unsigned int i = 0; i < pos.size(); ++i)
		{
			//std::cout << ":Sdf " << std::endl;
			for (unsigned int j = 0; j < pos[i].size(); ++j)
			{
				std::cout << pos[i][j].x << " " << pos[i][j].y << std::endl;
			}
			std::cout << "NEXT ROW" << std::endl;
		}*/
		height = pos.size();
		width = pos[0].size();
		//std::cout << "Sdf" << std::endl;
	}
	std::vector< std::vector<Position> > pos;
	int width;
	int height;
};

class Level
{
public:
	Level(int l, Player *player, std::vector<ALLEGRO_BITMAP*> a, std::vector<ALLEGRO_BITMAP*> c)
		:player(player), a(a), c(c)
	{
		init(l);
	};
	//initalize which level
	void init(int l);
	//start level
	void start();
	//reset current level
	void reset();
	//updates all visible entities
	void updateLevel();

	//getters and setts
	std::vector<Barrier> returnWalls();
	std::vector<TurnTile> returnTurnTiles();
	void setTurnTiles(const std::vector<TurnTile> v);
	std::vector<Collectable> returnCollectables();
	void setCollectables(const std::vector <Collectable> c);

	//whether game has started or not
	bool gameStart;
	Player* player;

	Score score;
private:

	std::vector<Barrier> walls;
	std::vector<TurnTile> turnTiles;
	std::vector<Collectable> collectables;

	std::vector<ALLEGRO_BITMAP*> a;
	std::vector<ALLEGRO_BITMAP*> c;

	Tile tile;

	Position playerpos;
};

