#include "stdafx.h"
#include "Level.h"

using namespace std;

void Level::init(int l)
{
	gameStart = false;
	player->isDead = false;

	player->tailList.clear();
	turnTiles.clear();
	walls.clear();
	collectables.clear();

	//stream
	fstream f;
	//info from stream
	string info;

	//get filename
	string filename;
	stringstream ss;
	ss << l;
	filename = "levels/lv" + ss.str();
	filename += ".txt";

	int tempx;
	int tempy;
	int tempx2;
	int tempy2;

	float xscreen;
	float yscreen;
	float x2screen;
	float y2screen;
	
	//open file based on type
	f.open(filename.c_str());
	if (f.is_open())
	{
		while (!f.eof())
		{
			tempx = tile.width;
			tempy = tile.height;
			tempx2 = tile.width;
			tempy2 = tile.height;
			f >> info;
			if (info == "Player")
			{
				f >> info;
				tempx *= atof(info.c_str());
				f >> info;
				tempy *= atof(info.c_str());
				//cout << "dfs" << endl;
				xscreen = tile.pos[tempy][tempx].x;
				yscreen = tile.pos[tempy][tempx].y;
				player->resetPos(xscreen, yscreen);
				TurnTile t(xscreen, yscreen, true, -1, a);
				//cout << player->posBegin.x << " " << player->posBegin.y << " " << player->posEnd.x << " " << player->posEnd.y << endl;
				turnTiles.push_back(t);
				playerpos.x = xscreen;
				playerpos.y = yscreen;
			}
			else if (info == "TurnTile")
			{
				f >> info;
				tempx *= atof(info.c_str());
				f >> info;
				tempy *= atof(info.c_str());
				xscreen = tile.pos[tempy][tempx].x;
				yscreen = tile.pos[tempy][tempx].y;
				TurnTile t(xscreen, yscreen, false, -1, a);
				turnTiles.push_back(t);
			}
			else if (info == "OneWay")
			{
				f >> info;
				tempx *= atof(info.c_str());
				f >> info;
				tempy *= atof(info.c_str());
				xscreen = tile.pos[tempy][tempx].x;
				yscreen = tile.pos[tempy][tempx].y;
				f >> info;
				TurnTile t(xscreen, yscreen, false, atoi(info.c_str()), a);
				turnTiles.push_back(t);
			}
			else if (info == "Bronze")
			{
				f >> info;
				tempx *= atof(info.c_str());
				f >> info;
				tempy *= atof(info.c_str());
				xscreen = tile.pos[tempy][tempx].x;
				yscreen = tile.pos[tempy][tempx].y;
				Collectable c(xscreen, yscreen, BRONZE, c[BRONZE]);
				collectables.push_back(c);
			}
			else if (info == "Star")
			{
				f >> info;
				tempx *= atof(info.c_str());
				f >> info;
				tempy *= atof(info.c_str());
				xscreen = tile.pos[tempy][tempx].x;
				yscreen = tile.pos[tempy][tempx].y;
				Collectable c(xscreen, yscreen, STAR, c[STAR]);
				collectables.push_back(c);
				score.starsLeft++;
			}
			else if (info == "Barrier")
			{
				f >> info;
				tempx *= atof(info.c_str());
				f >> info;
				tempy *= atof(info.c_str());
				f >> info;
				tempx2 *= atof(info.c_str());
				f >> info;
				tempy2 *= atof(info.c_str());

				xscreen = tile.pos[tempy][tempx].x;
				yscreen = tile.pos[tempy][tempx].y;
				x2screen = tile.pos[tempy2][tempx2].x;
				y2screen = tile.pos[tempy2][tempx2].y;
				cout << "Creating barrier: ";
				cout << xscreen << " " << yscreen << " " << x2screen << " " << y2screen << endl;
				Barrier b(xscreen, yscreen, x2screen, y2screen);
				walls.push_back(b);
			}
			else
			{
				cout << "Could not find category." << endl;
			}
		}
	}
	else
	{
		cerr << "Could not open: " + filename << endl;
	}
	f.close();
	/*
	player->resetPos(0, 0);
	playerpos.x = 0;
	playerpos.y = 0;
	TurnTile t1(0, 200, a);
	turnTiles.push_back(t1);
	TurnTile t2(50, 200, a);
	turnTiles.push_back(t2);
	TurnTile t3(50, 50, a);
	turnTiles.push_back(t3);
	TurnTile t4(200, 50, a);
	turnTiles.push_back(t4);
	Barrier b1(500, 500, 300, 500);
	Barrier b2(100, 100, 100, 500);
	Barrier b3(150, 100, 150, 500);
	walls.push_back(b1);
	walls.push_back(b2);
	walls.push_back(b3);
	Collectable c1(550, 200, BRONZE, c[BRONZE]);
	Collectable c2(550, 300, SILVER, c[SILVER]);
	Collectable c3(550, 400, GOLD, c[GOLD]);
	Collectable c4(550, 500, STAR, c[STAR]);
	collectables.push_back(c1);
	collectables.push_back(c2);
	collectables.push_back(c3);
	collectables.push_back(c4);*/
}

//start level
void Level::start()
{
	cout << "Game has started." << endl;
	if (!gameStart)
	{
		gameStart = true;
		player->isDead = false;
	}

}

void Level::reset()
{
	player->tailList.clear();
	player->resetPos(playerpos.x, playerpos.y);
	gameStart = false;
	player->isDead = false;
	//reset collectables
	for (unsigned int i = 0; i < collectables.size(); ++i)
	{
		collectables[i].obtained = false;
	}
}

//updates all visible entities
void Level::updateLevel()
{
	for (unsigned int i = 0; i < walls.size(); ++i) walls[i].updateBarrier();
	for (unsigned int i = 0; i < turnTiles.size(); ++i) turnTiles[i].updateTurnTile();
	for (unsigned int i = 0; i < collectables.size(); ++i) if (!collectables[i].obtained) collectables[i].updateCollectable();
}

vector<Barrier> Level::returnWalls() { return walls; }

vector<TurnTile> Level::returnTurnTiles() { return turnTiles; }
void Level::setTurnTiles(const std::vector<TurnTile> t) { turnTiles = t; }

vector<Collectable> Level::returnCollectables() { return collectables; }
void Level::setCollectables(const std::vector <Collectable> c) { collectables = c; }