#include "Player.h"

Player::Player(int _screenWidth, int _screenHeight)
{
	width = 32;
	height = 32;
	speed = 4;
	lives = 3;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	x = screenWidth / 2 - width / 2;
	y = screenHeight / 2 - height / 2;
	bulletDir = dir(BULLET_RIGHT);
	bullet = new Bullet(x, y, screenWidth, screenHeight, bulletDir);

	sprite = al_load_bitmap("assets/player.png");
	if (!sprite)
		fprintf(stderr, "failed to create player bitmap!\n");

	shootSound = al_load_sample("assets/shootSound.wav");
	if (!shootSound) {
		fprintf(stderr,"Audio clip sample not loaded!\n");		
	}

	hurtSound = al_load_sample("assets/hurtSound.wav");
	if (!hurtSound) {
		fprintf(stderr, "Audio clip sample not loaded!\n");
	}
}
Player::~Player()
{	
	al_destroy_bitmap(sprite);
	al_destroy_sample(shootSound);
	al_destroy_sample(hurtSound);	
	delete bullet;
}
void Player::Update(ALLEGRO_EVENT ev)
{	
		Movement(ev);	
		Shoot(ev);		
		OOB();
}
void Player::Movement(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if (ev.keyboard.keycode == ALLEGRO_KEY_A)
			key[KEY_LEFT] = 1;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_D)
			key[KEY_RIGHT] = 1;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_W)
			key[KEY_UP] = 1;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
			key[KEY_DOWN] = 1;
	}
	if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		if (ev.keyboard.keycode == ALLEGRO_KEY_A)
			key[KEY_LEFT] = 0;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_D)
			key[KEY_RIGHT] = 0;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_W)
			key[KEY_UP] = 0;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
			key[KEY_DOWN] = 0;		
	}
	if (key[KEY_LEFT])
	{
		x -= speed;
		bulletDir = dir(BULLET_LEFT);
	}
	else if (key[KEY_RIGHT])
	{
		x += speed;
		bulletDir = dir(BULLET_RIGHT);
	}
	else if (key[KEY_UP])
	{
		y -= speed;
		bulletDir = dir(BULLET_UP);
	}
	else if (key[KEY_DOWN])
	{
		y += speed;
		bulletDir = dir(BULLET_DOWN);
	}	
}
void Player::Draw() const
{
	al_draw_bitmap(sprite, x, y, 0);
	if (bullet->GetAlive())
		bullet->Draw();
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
void Player::Shoot(ALLEGRO_EVENT ev)
{
	if (ev.keyboard.keycode == ALLEGRO_KEY_K && !bullet->GetAlive())
	{		
		al_stop_sample(&hurtID);
		al_stop_sample(&shootID);
		al_play_sample(shootSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &shootID);
		bullet->Reset(x, y, bulletDir);
	}
	if (bullet->GetAlive())
		bullet->Update();
}

void Player::SetX(float _x)
{
	x += _x;
}
void Player::SetY(float _y)
{
	y += _y;
}
bool Player::Alive() const
{
	if (lives <= 0)
		return false;
	else
		return true;
}
void Player::OnDeath()
{
	al_stop_sample(&hurtID);	
	al_stop_sample(&shootID);
	al_play_sample(hurtSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hurtID);
	lives--;
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
Bullet* Player::GetBullet()
{
	return bullet;
}
ALLEGRO_BITMAP* Player::GetBitmap() const
{
	return sprite;
}
std::string Player::GetLives()
{
	std::string livesText = std::to_string(lives);
	return "Lives: " + livesText;
}
