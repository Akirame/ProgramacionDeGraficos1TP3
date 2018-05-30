#include "Player.h"

Player::Player(int _screenWidth, int _screenHeight)
{
	width = 32;
	height = 32;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	x = screenWidth / 2 - width / 2;
	y = screenHeight / 2 - height / 2;
	sprite = al_load_bitmap("assets/player.jpg");
	if (!sprite)
		fprintf(stderr, "failed to create player bitmap!\n");
}


Player::~Player()
{
	if (!sprite)
		delete sprite;
}
void Player::Update(ALLEGRO_EVENT ev)
{	
		Movement(ev);	
		OOB();
}
void Player::Movement(ALLEGRO_EVENT ev)
{
	if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
		y -= 10;
	else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
		y += 10;
	else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
		x -= 10;
	else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
		x += 10;
}
void Player::SetX(float _x)
{
	x += _x;
}
void Player::SetY(float _y)
{
	y += _y;
}
float Player::GetX() const
{
	return x;
}
float Player::GetY() const
{
	return y;
}
float Player::GetHeight() const
{
	return height;
}
float Player::GetWidht() const
{
	return width;
}
ALLEGRO_BITMAP* Player::GetBitmap() const
{
	return sprite;
}
void Player::OOB()
{
	if (y <= 0)
		y = 0;
	if (y >= screenHeight - height)
		y = screenHeight - height;
	if (x <= 0)
		x = 0;
	if (x >= screenWidth - width)
		x = screenWidth - width;
}
