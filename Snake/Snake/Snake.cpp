// Snak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_native_dialog.h"

#include "Player.h"
#include "Level.h"
#include "Globals.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//mouse position
int mpos_x = -1;
int mpos_y = -1;

int starsLeft;
int cl = 0;
int FPS = 60;
int main(int argc, char** argv)
{
	ALLEGRO_DISPLAY *display = NULL;

	//Init Allegro
	if (!al_init())
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}
	//init audio
	if (!al_install_audio()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize audio!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}
	
	if (!al_init_acodec_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize audio codecs!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}

	if (!al_reserve_samples(1)) {
		al_show_native_message_box(display, "Error", "Error", "Failed to reserve samples!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}

	//Init Images
	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}

	//Init Display and window name
	ALLEGRO_DISPLAY_MODE disp_data;
	al_set_app_name("Snak Prototype by Rica Feng!");
	display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	if (!display)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to create display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}

	//Init fonts
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font24 = al_load_font("fonts/ariblk.ttf", 16, 0);
	if (!font24)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load font!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return EXIT_FAILURE;
	}

	vector<ALLEGRO_BITMAP*> coins;
	ALLEGRO_BITMAP *star = al_load_bitmap("images/star.png");
	if (!star)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load star!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}

	ALLEGRO_BITMAP *bronze = al_load_bitmap("images/bronze.png");
	if (!bronze)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load bronze!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}

	ALLEGRO_BITMAP *silver = al_load_bitmap("images/silver.png");
	if (!silver)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load silver!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}

	ALLEGRO_BITMAP *gold = al_load_bitmap("images/gold.png");
	if (!gold)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load gold!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}
	coins.push_back(bronze);
	coins.push_back(silver);
	coins.push_back(gold);
	coins.push_back(star);

	vector<ALLEGRO_BITMAP*> arrows;
	//draw image
	ALLEGRO_BITMAP *arrowup = al_load_bitmap("images/arrow_up.png");
	if (!arrowup)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load arrowup!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}
	arrows.push_back(arrowup);

	ALLEGRO_BITMAP *arrowdown = al_load_bitmap("images/arrow_down.png");
	if (!arrowdown)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load arrowdown!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}
	arrows.push_back(arrowdown);

	ALLEGRO_BITMAP *arrowleft = al_load_bitmap("images/arrow_left.png");
	if (!arrowleft)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load arrowleft!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}
	arrows.push_back(arrowleft);

	ALLEGRO_BITMAP *arrowright = al_load_bitmap("images/arrow_right.png");
	if (!arrowright)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load arrowright!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}
	arrows.push_back(arrowright);

	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	bool done = false;
	bool draw = false;

	//construct player
	Player player(2.5, event_queue);
	//construct level
	Level currentLevel(cl, &player, arrows, coins);
	cout << player.posBegin.x << " " << player.posBegin.y << " " << player.posEnd.x << " " << player.posEnd.y << endl;
	al_start_timer(timer);
	while (!done)
	{
		//draw circle
		//al_draw_filled_circle(w / 2, h / 2, 30, Color.yellow);
		//draw images
		//al_draw_bitmap(image, 200, 200, 0);
		//draw fonts
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 10, 0, "Click on the yellow turn tiles to");
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 30, 0, "change its direction.");
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 50, 0, "Press Enter to start level.");
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 70, 0, "Press R to restart level.");
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 90, 0, "Press Esc to quit.");
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 130, 0, "Get all the stars.");
		al_draw_text(font24, al_map_rgb(0, 0, 0), 10, 150, 0, "Coins are optional.");
		while (!al_is_event_queue_empty(event_queue))
		{
			ALLEGRO_EVENT events;
			al_wait_for_event(event_queue, &events);

			switch (events.type)
			{
			case ALLEGRO_EVENT_KEY_DOWN:
				currentLevel.player->getInput(events);
				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_ENTER:
					currentLevel.start();
					break;
				case ALLEGRO_KEY_R:
					currentLevel.init(cl);
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES:
				mpos_x = events.mouse.x;
				mpos_y = events.mouse.y;
				//cout << mpos_x << " " << mpos_y << endl;
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				if (events.mouse.button & 1) // left click
				{
					vector<TurnTile> t = currentLevel.returnTurnTiles();
					for (unsigned int i = 0; i < t.size() && !currentLevel.gameStart; ++i)
					{
						//cout << "detect click" << endl;
						t[i].checkClick(mpos_x, mpos_y);
					}
					currentLevel.setTurnTiles(t);
				}
				break;
			case ALLEGRO_EVENT_TIMER: //only update when we hit next frame
				draw = true;
				break;
			}
		}
		if (draw) //DRAW CALLS
		{
			//cout << player.posBegin.x << " " << player.posBegin.y << " " << player.posEnd.x << " " << player.posEnd.y << endl;
			draw = false;
			currentLevel.player->updatePlayer();
			//only check collisions if game has started
			if (currentLevel.gameStart)
			{
				//cout << player.posBegin.x << " " << player.posBegin.y << " " << player.posEnd.x << " " << player.posEnd.y << endl;
				//cout << "sdf" << endl;
				currentLevel.player->collideBarrier(currentLevel.returnWalls());
				currentLevel.player->collideTurnTile(currentLevel.returnTurnTiles());
				currentLevel.setCollectables(currentLevel.player->collideCollectable(currentLevel.returnCollectables()));
			}

			currentLevel.updateLevel();

			al_flip_display();
			al_clear_to_color(al_map_rgb(255, 255, 255));
		}

		//check if won
		starsLeft = 0;
		for (unsigned int i = 0; i < currentLevel.returnCollectables().size(); ++i)
		{
			if (!currentLevel.returnCollectables()[i].obtained && 
				currentLevel.returnCollectables()[i].type == STAR) starsLeft++;
		}
		if (starsLeft == 0)
		{
			cout << "Level Complete!" << endl;
			al_rest(3.0);
			if (cl == 3)
			{
				done = true;
			}
			else
			{
				currentLevel.init(++cl);
			}
		}

	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(arrowup);
	al_destroy_bitmap(arrowdown);
	al_destroy_bitmap(arrowleft);
	al_destroy_bitmap(arrowright);
	return 0;
}

