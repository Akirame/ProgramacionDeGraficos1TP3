#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include "allegro5\allegro.h"
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
enum dir
{
	BULLET_LEFT,
	BULLET_RIGHT,
	BULLET_UP,
	BULLET_DOWN,
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
	bool alive;
	dir direction;
	ALLEGRO_BITMAP* sprite = NULL;
public:
	Bullet(int startX, int startY,int screenWidth, int screenHeight,dir _directions);
	~Bullet();			
	void Reset(int startX,int startY,dir _directions);
	void KillBullet();
	float GetX() const;
	float GetY() const;	
	float GetHeight() const;
	float GetWidht() const;
	bool GetAlive() const;
	void BiggerBullet();
	ALLEGRO_BITMAP* GetBitmap() const;
	void Movement();
	void Update();
	void OOB();
	void Draw() const;
	void SetSize(int _width, int _height);
};
#endif