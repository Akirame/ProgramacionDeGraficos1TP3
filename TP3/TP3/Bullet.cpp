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
	speed = 7;
	scale = 1;
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
	al_draw_scaled_bitmap(sprite, 0, 0, width, height, x, y, width*scale, height*scale, 0);
}
//dependiendo de la Dir se mueve diferente
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
//Al chocar un costado muere la bala
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
void Bullet::Reset(int startX, int startY, dir _directions)
{
	alive = true;
	x = startX;
	y = startY;
	direction = _directions;
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
	return height * scale;
}
float Bullet::GetWidht() const
{
	return width;
}
ALLEGRO_BITMAP* Bullet::GetBitmap() const
{
	return sprite;
}
bool Bullet::GetAlive() const
{
	return alive;
}
void Bullet::BiggerBullet()
{
	scale += 1.2f;
}
void Bullet::SetSize(int _width, int _height)
{
	width = _width;
	height = _height;
}
