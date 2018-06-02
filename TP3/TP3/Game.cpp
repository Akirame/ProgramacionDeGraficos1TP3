#include "Game.h"



Game::Game()
{
	display = NULL;
	event_queue = NULL;
	timer = NULL;
	font = NULL;
	_gameOver = false;
	_menu = true;
	redraw = true;
}
Game::~Game()
{
}
bool Game::InitAll()
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return false;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return false;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return false;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_font_addon())
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_font_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}
	if (!al_init_ttf_addon())
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_ttf_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}


	font = al_load_ttf_font("assets/arial_narrow_7.ttf", 72, 0);

	if (!font)
	{
		fprintf(stderr, "Could not load 'assets/arial_narrow_7.ttf'.\n");
		return -1;
	}

	player = new Player(SCREEN_W, SCREEN_H);
	enemy1 = new Enemy(SCREEN_W, SCREEN_H, 32, 32);

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	if (!event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		delete player;
		delete enemy1;
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_flip_display();

	al_start_timer(timer);
	return true;
}
int Game::MainMenu()
{
	while (_menu)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			_menu = false;
			_gameOver = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
				_menu = false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 640 / 2, (480 / 3), ALLEGRO_ALIGN_CENTRE, "Press Space to start!");
			al_flip_display();
		}
	}
	return 0;
}
int Game::UpdateGame()
{
	while (!_gameOver)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (player)
				player->Update(ev);
			if (enemy1)
				enemy1->Update(ev);
			if (enemy1)
			{
				if (bounding_box_collision(player->GetX(), player->GetY(), player->GetWidht(), player->GetHeight(),
					enemy1->GetX(), enemy1->GetY(), enemy1->GetWidht(), enemy1->GetHeight()))
					_gameOver = true;
				if (bounding_box_collision(player->GetBullet()->GetX(), player->GetBullet()->GetY(), player->GetBullet()->GetWidht(), player->GetBullet()->GetHeight()
					, enemy1->GetX(), enemy1->GetY(), enemy1->GetWidht(), enemy1->GetHeight()))
				{
					if (enemy1)
					{
						delete enemy1;
						enemy1 = NULL;
					}
					player->GetBullet()->KillBullet();
				}
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			_gameOver = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (player)
				player->Update(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (player)
				player->Update(ev);
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 40, 0));
			if (player)
				player->Draw();
			if (enemy1)
				enemy1->Draw();
			al_flip_display();
		}
	}
	if (player)
		delete player;
	if (enemy1)
		delete enemy1;
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
bool Game::bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
	if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
		(b1_y > b2_y + b2_h - 1) || // is b1 under b2?
		(b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
		(b2_y > b1_y + b1_h - 1))   // is b2 under b1?
	{
		// no collision
		return false;
	}
	// collision
	return true;
}
