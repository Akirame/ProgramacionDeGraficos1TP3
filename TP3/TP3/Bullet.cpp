#include "Bullet.h"


Bullet::Bullet(int _screenWidth, int _screenHeight)
{
	width = 12;
	height = 12;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	x = screenWidth / 2 - width / 2;
	y = screenHeight / 2 - height / 2;
	speed = 5;
	sprite = al_load_bitmap("assets/player.png");
	if (!sprite)
		fprintf(stderr, "failed to create player bitmap!\n");
}


Bullet::~Bullet()
{
	if (!sprite)
		delete sprite;
}
void Bullet::Update()
{
	Movement();
	OOB();
}
void Bullet::Movement()
{	
	if (direction == dir(UP))
	{
		y -= speed;		
	}
	if (direction == dir(DOWN))
	{
		y += speed;
	}
	if (direction == dir(LEFT))
	{
		x -= speed;
	}
	if (direction == dir(RIGHT))
	{
		x += speed;
	}
}
void Bullet::SetX(float _x)
{
	x += _x;
}
void Bullet::SetY(float _y)
{
	y += _y;
}
void Bullet::SetDirection(dir _direction)
{
	direction = _direction;
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
void Bullet::OOB()
{
	if (y <= 0)
		delete this;
	if (y >= screenHeight - height)
		delete this;
	if (x <= 0)
		delete this;
	if (x >= screenWidth - width)
		delete this;
}
