#include "PowerUp.h"

PowerUp::PowerUp(int _screenWidth, int _screenHeight) : screenWidth(_screenWidth), screenHeight(_screenHeight)
{
	typePower = typeOfPower(rand() & LAST);
}
PowerUp::~PowerUp()
{
	al_destroy_bitmap(sprite);
}
void PowerUp::ActivePower(Player &p)
{
	switch (typePower)
	{
	case BIG:
		break;
	case SPEED:
		break;
	case INVUL:
		break;
	case LIVES:
		break;	
	}
}
void PowerUp::SetX(float _x)
{
	x = _x;
}
void PowerUp::SetY(float _y)
{
	y = _y;
}
float PowerUp::GetX() const 
{
	return x;
}
float PowerUp::GetY() const
{
	return y;
}
float PowerUp::GetHeight() const
{
	return height;
}
float PowerUp::GetWidht() const
{
	return width;
}
ALLEGRO_BITMAP* PowerUp::GetBitmap()
{
	return sprite;
}
typeOfPower PowerUp::GetType() const
{
	return typePower;
}