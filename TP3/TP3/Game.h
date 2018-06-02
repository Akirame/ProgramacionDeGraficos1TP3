#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5\allegro_font.h"
#include <allegro5/allegro_ttf.h>
#include "Player.h"
#include "Enemy.h"
#include <string>


class Game
{
	const float FPS = 60;
	const int SCREEN_W = 640;
	const int SCREEN_H = 480;
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *scoreText;
	ALLEGRO_FONT *livesText;
	Player* player;
	Enemy* enemy1;
	Enemy* enemy2;
	bool _gameOver;
	bool _menu;
	bool redraw;
	int score;
public:
	Game();
	~Game();
	bool InitAll();
	bool bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);
	int UpdateGame();
	int MainMenu();
	void AddScore();	
	std::string GetScore();
	void GameOver();
};
#endif

