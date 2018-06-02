#include "Enemy.h"

Enemy::Enemy(int _screenWidth, int _screenHeight, int startX, int startY)
{
	srand(time(0));
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

void Enemy::randDir()
{	
	dir = static_cast<directions>(rand() % ENEMY_LAST);	
}
Enemy::~Enemy()
{	
	al_destroy_bitmap(sprite);
}
void Enemy::Update(ALLEGRO_EVENT ev)
{
	Movement(ev);
}
void Enemy::Draw() const
{	
	al_draw_bitmap(sprite, x, y, 0);
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
void Enemy::OOB()
{
	if (y <= 0)
		randDir();
	if (y >= screenHeight - height)
		randDir();
	if (x <= 0)
		randDir();
	if (x >= screenWidth - width)
		randDir();
}
void Enemy::SetX(float _x)
{
	x += _x;
}
void Enemy::SetY(float _y)
{
	y += _y;
}
float Enemy::GetX() const
{
	return x;
}
float Enemy::GetY() const
{
	return y;
}
float Enemy::GetHeight() const
{
	return height;
}
float Enemy::GetWidht() const
{
	return width;
}
float Enemy::GetSpeed() const
{
	return speed;
}
ALLEGRO_BITMAP* Enemy::GetBitmap()
{
	return sprite;
}

