#include "Game.h"

Game::Game()
{
	srand(time(0));
	display = NULL;
	event_queue = NULL;
	timer = NULL;
	scoreText = NULL;
	livesText = NULL;
	enemies = new list<Enemy>();
	_gameOver = false;
	_menu = true;
	_finalMenu = true;
	redraw = true;
	score = 0;
	cantEnemies = 4;
	enemiesStronger = false;
}
Game::~Game()
{
	delete player;
	enemies->clear();
	delete enemies;
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(scoreText);
	al_destroy_font(livesText);
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

	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		return false;
	}
	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
	if (!al_reserve_samples(1)) {
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	scoreText = al_load_ttf_font("assets/arial_narrow_7.ttf", 32, 0);
	if (!scoreText)
	{
		fprintf(stderr, "Could not load 'assets/arial_narrow_7.ttf'.\n");
		return -1;
	}

	livesText = al_load_ttf_font("assets/arial_narrow_7.ttf", 32, 0);
	if (!livesText)
	{
		fprintf(stderr, "Could not load 'assets/arial_narrow_7.ttf'.\n");
		return -1;
	}

	player = new Player(SCREEN_W, SCREEN_H);
	pUp = new PowerUp(SCREEN_W, SCREEN_H);

	//Instanciacion enemigos
	for (int i = 0; i < cantEnemies; i++)
	{
		Enemy* enemy = new Enemy(SCREEN_W, SCREEN_H);
		enemies->push_front(*enemy);
	}
	iterEnemyBegin = enemies->begin();
	iterEnemyEnd = enemies->end();

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		delete player;
		enemies->clear();
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
			_finalMenu = false;
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
			al_draw_text(scoreText, al_map_rgb(255, 255, 255), 640 / 2, (480 / 3), ALLEGRO_ALIGN_CENTRE, "Press Space to start!");
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
			player->Update(ev);

			//Update y colision enemigos
			for (list<Enemy>::iterator iter = iterEnemyBegin; iter != iterEnemyEnd; iter++)
			{
				iter->Update(ev);
				if (bounding_box_collision(player->GetX(), player->GetY(), player->GetWidht(), player->GetHeight(),
					iter->GetX(), iter->GetY(), iter->GetWidht(), iter->GetHeight()))
				{
					player->OnDeath();
					iter->Reset();
				}
				if (player->GetBullet()->GetAlive())
					if (bounding_box_collision(player->GetBullet()->GetX(), player->GetBullet()->GetY(), player->GetBullet()->GetWidht(), player->GetBullet()->GetHeight()
						, iter->GetX(), iter->GetY(), iter->GetWidht(), iter->GetHeight()))
					{
						player->GetBullet()->KillBullet();
						AddScore();
						iter->Reset();
					}
				if (pUp->Alive())
				{
					if (bounding_box_collision(player->GetX(), player->GetY(), player->GetWidht(), player->GetHeight(),
						pUp->GetX(), pUp->GetY(), pUp->GetWidht(), pUp->GetHeight()))
					{
						pUp->ActivePower(player);
						contaUpgrades = -200;
					}
				}
				
			}
			if (contaUpgrades < 360)
			{
				contaUpgrades++;				
			}
			else
			{
				pUp->Spawn();
				contaUpgrades = 0;
			}
			GameOver();
			Difficulty();
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			_gameOver = true;
			_finalMenu = false;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (player)
				player->Update(ev);
			if (ev.keyboard.keycode == ALLEGRO_KEY_Z)
			{
				pUp->Spawn();
			}				
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
			player->Draw();
			pUp->Draw();
			for (list<Enemy>::iterator iter = iterEnemyBegin; iter != iterEnemyEnd; iter++)
			{
				iter->Draw();
			}
			al_draw_text(scoreText, al_map_rgb(255, 255, 255), 70, 1, ALLEGRO_ALIGN_CENTRE, GetScore().c_str());
			al_draw_text(livesText, al_map_rgb(255, 255, 255), 60, 40, ALLEGRO_ALIGN_CENTRE, player->GetLives().c_str());
			al_flip_display();
		}

	}
	return 0;
}
int Game::FinalMenu()
{
	scoreText = al_load_ttf_font("assets/arial_narrow_7.ttf", 72, 0);
	livesText = al_load_ttf_font("assets/arial_narrow_7.ttf", 72, 0);
	while (_finalMenu)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			_finalMenu = false;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
				_finalMenu = false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(scoreText, al_map_rgb(255, 255, 255), SCREEN_W / 3, (SCREEN_H / 3), ALLEGRO_ALIGN_CENTRE, GetScore().c_str());
			al_flip_display();
		}
	}

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
void Game::AddScore()
{
	score += 10;
}
std::string Game::GetScore()
{
	std::string scoreText = std::to_string(score);
	return "Score: " + scoreText;
}
void Game::GameOver()
{
	if (player->Alive())
		_gameOver = false;
	else
		_gameOver = true;
}
void Game::Difficulty()
{
	if (score >= 200 && !enemiesStronger)
	{
		Enemy* enemy = new Enemy(SCREEN_W, SCREEN_H);
		enemies->push_front(*enemy);
		iterEnemyBegin = enemies->begin();
		iterEnemyEnd = enemies->end();
		for (list<Enemy>::iterator iter = iterEnemyBegin; iter != iterEnemyEnd; iter++)
		{
			iter->speedPlusPlus();
		}
		enemiesStronger = true;
	}
}


