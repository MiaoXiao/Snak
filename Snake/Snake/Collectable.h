#pragma once
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#include <iostream>
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

		if (type == STAR)
		{
			sample = al_load_sample("sounds/star.wav");
			if (!sample) {
				std::cout << "star.wav did not load!" << std::endl;
			}
		}
		else
		{
			sample = al_load_sample("sounds/coin.wav");
			if (!sample) {
				std::cout << "coin.wav did not load!" << std::endl;
			}
		}

	}
	void updateCollectable();
	void playSound();
	bool obtained;
	int type;
private:
	int id;
	
	int score;
	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sample;
};

