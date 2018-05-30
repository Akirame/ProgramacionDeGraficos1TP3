#include "Enemy.h"

Enemy::Enemy(int _screenWidth, int _screenHeight, int startX, int startY)
{
	width = 32;
	height = 32;
	speed = 3;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	x = startX;
	y = startY;
	sprite = al_load_bitmap("assets/enemy.png");
	if (!sprite)
		fprintf(stderr, "failed to create enemy bitmap!\n");
}

Enemy::~Enemy()
{
	if (!sprite)
		delete sprite;
}
void Enemy::Update(ALLEGRO_EVENT ev)
{
	Movement(ev);
}
// si choca contra el costado derecho vuelve
void Enemy::Movement(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		if (x < 0)
			speed *= -1;
		else if (x + width > screenWidth)
			speed *= -1;
		x += speed;
	}
}
void Enemy::SetX(float _x)
{
	x += _x;
}
void Enemy::SetY(float _y)
{
	y += _y;
}
float Enemy::GetX()
{
	return x;
}
float Enemy::GetY()
{
	return y;
}
float Enemy::GetHeight()
{
	return height;
}
float Enemy::GetWidht()
{
	return width;
}
float Enemy::GetSpeed()
{
	return speed;
}
ALLEGRO_BITMAP* Enemy::GetBitmap()
{
	return sprite;
}

