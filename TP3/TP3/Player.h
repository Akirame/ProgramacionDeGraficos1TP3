#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "allegro5\allegro.h"
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Bullet.h"

enum GAME_KEYS
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN
};

class Player
{
private:
	int width;
	int height;
	int screenWidth;
	int screenHeight;
	float speed;
	float x;
	float y;
	int lives;
	int key[4] = { 0,0,0,0 };
	dir bulletDir;
	Bullet* bullet;
	ALLEGRO_BITMAP* sprite = NULL;
	ALLEGRO_SAMPLE* shootSound = NULL;
	ALLEGRO_SAMPLE* hurtSound = NULL;
	ALLEGRO_SAMPLE_ID shootID;
	ALLEGRO_SAMPLE_ID hurtID;
public:
	Player(int screenWidth, int screenHeight);
	~Player();

	void Movement(ALLEGRO_EVENT ev);
	void Update(ALLEGRO_EVENT ev);
	void OOB();
	void Draw() const;
	void Shoot(ALLEGRO_EVENT ev);
	void SetX(float _x);
	void SetY(float _y);
	bool Alive() const;
	void OnDeath();
	float GetX() const;
	float GetY() const;
	float GetHeight() const;
	float GetWidht() const;
	Bullet* GetBullet();
	ALLEGRO_BITMAP* GetBitmap() const;
	std::string GetLives();
};
#endif

