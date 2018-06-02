#include "Bullet.h"


Bullet::Bullet(int startX,int startY, int _screenWidth, int _screenHeight,dir _direction)
{
	alive = false;
	width = 12;
	height = 12;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	x = screenWidth / 2 - width / 2;
	y = screenHeight / 2 - height / 2;
	direction = _direction;
	speed = 5;
	sprite = al_load_bitmap("assets/bullet.png");
	if (!sprite)
		fprintf(stderr, "failed to create player bitmap!\n");
}
Bullet::~Bullet()
{	
	al_destroy_bitmap(sprite);
}
void Bullet::Update()
{	
	Movement();	
	OOB();
}
void Bullet::Draw() const
{
	al_draw_bitmap(sprite, x, y, 0);
}
void Bullet::Movement()
{	
	if (direction == dir(BULLET_UP))
	{
		y -= speed;		
	}
	if (direction == dir(BULLET_DOWN))
	{
		y += speed;
	}
	if (direction == dir(BULLET_LEFT))
	{
		x -= speed;
	}
	if (direction == dir(BULLET_RIGHT))
	{
		x += speed;
	}
}
void Bullet::KillBullet() 
{
	alive = false;
}
void Bullet::OOB()
{
	if (y <= 0)
		alive = false;
	if (y >= screenHeight - height)
		alive = false;
	if (x <= 0)
		alive = false;
	if (x >= screenWidth - width)
		alive = false;
}
float Bullet::GetX() const
{
	return x;
}
float Bullet::GetY() const
{
	return y;
}
float Bullet::GetHeight() const
{
	return height;
}
float Bullet::GetWidht() const
{
	return width;
}
ALLEGRO_BITMAP* Bullet::GetBitmap() const
{
	return sprite;
}
bool Bullet::GetAlive()
{
	return alive;
}
void Bullet::Reset(int startX, int startY, dir _directions)
{
	alive = true;
	x = startX;
	y = startY;
	direction = _directions;
}