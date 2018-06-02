#include "Enemy.h"

Enemy::Enemy(int _screenWidth, int _screenHeight,int startX,int startY)
{
	srand(time(0));
	width = 32;
	height = 32;
	speed = 3;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	x = startX;
	y = startY;
	RandomDir();
	sprite = al_load_bitmap("assets/enemy.png");
	if (!sprite)
		fprintf(stderr, "failed to create enemy bitmap!\n");	
}

Enemy::~Enemy()
{	
	al_destroy_bitmap(sprite);
}

//Random a direccion cuando toca un lateral
void Enemy::RandomDirOnTouch(directions _dir[])
{	
	int randIndex = rand() % 3;
	dir = _dir[randIndex];
}

void Enemy::Update(ALLEGRO_EVENT ev)
{	
	Movement(ev);
	OOB();
}

void Enemy::Draw() const
{	
	al_draw_bitmap(sprite, x, y, 0);
}

//dependiendo de la Dir se mueve diferente
void Enemy::Movement(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		switch (dir)
		{
		case ENEMY_UP:
			y -= speed;
			break;
		case ENEMY_UP_LEFT:
			y -= speed;
			x -= speed;
			break;
		case ENEMY_UP_RIGHT:
			y -= speed;
			x += speed;
			break;
		case ENEMY_LEFT:
			x -= speed;
			break;
		case ENEMY_RIGHT:
			x += speed;
			break;
		case ENEMY_DOWN:
			y += speed;
			break;
		case ENEMY_DOWN_LEFT:
			y += speed;
			x -= speed;
			break;
		case ENEMY_DOWN_RIGHT:
			y += speed;
			x += speed;
			break;
		case ENEMY_LAST:
			break;
		}
	}
}

//Al chocar contra un costado cambia su direccion dependiendo de que lado choco
void Enemy::OOB()
{
	if (y <= 0)
		RandomDirOnTouch(touchUp);
	if (y >= screenHeight - height)
		RandomDirOnTouch(touchDown);
	if (x <= 0)
		RandomDirOnTouch(touchLeft);
	if (x >= screenWidth - width)
		RandomDirOnTouch(touchRight);
}

//Reset a cualquier punto en la pantalla y direcci�n
void Enemy::Reset()
{	
	RandomPoint();
	RandomDir();
}

//Punto random en la pantalla
void Enemy::RandomPoint()
{
	x = rand() % screenWidth;
	y = rand() % screenHeight;
}

//random a direccion en cualquier direccion
void Enemy::RandomDir() 
{
	dir = static_cast<directions>(rand() % ENEMY_LAST);
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
