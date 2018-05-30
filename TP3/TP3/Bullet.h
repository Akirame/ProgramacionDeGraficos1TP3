#ifndef BULLET_H
#define BULLET_H
#include "allegro5\allegro.h"
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
enum dir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};
class Bullet
{
private:
	int width;
	int height;
	int screenWidth;
	int screenHeight;
	float x;
	float y;
	float speed;
	dir direction;
	ALLEGRO_BITMAP* sprite = NULL;
public:
	Bullet(int screenWidth, int screenHeight);
	~Bullet();
	void SetX(float _x);
	void SetY(float _y);
	void SetDirection(dir _direction);
	float GetX() const;
	float GetY() const;	
	float GetHeight() const;
	float GetWidht() const;
	ALLEGRO_BITMAP* GetBitmap() const;
	void Movement();
	void Update();
	void OOB();
};
#endif