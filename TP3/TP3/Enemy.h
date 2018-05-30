#ifndef ENEMY_H
#define ENEMY_H
#include "allegro5\allegro.h"
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>

class Enemy {

private:
	int width;
	int height;
	int screenWidth;
	int screenHeight;
	float x;
	float y;
	float speed;
	ALLEGRO_BITMAP* sprite = NULL;
public:
	Enemy(int screenWidth, int screenHeight);
	~Enemy();
	void SetX(float _x);
	void SetY(float _y);
	float GetX();
	float GetY();
	float GetHeight();
	float GetWidht();
	float GetSpeed();
	ALLEGRO_BITMAP* GetBitmap();
	void Movement(ALLEGRO_EVENT ev);
	void Update(ALLEGRO_EVENT ev);

};
#endif

