#include "PowerUp.h"

PowerUp::PowerUp(int _screenWidth, int _screenHeight) : 
	screenWidth(_screenWidth), screenHeight(_screenHeight),
	alive(false),
	width(32),
	height(32)
{		
	spriteBig = al_load_bitmap("assets/bigBullet.png");
	if (!spriteBig)
		fprintf(stderr, "failed to create spriteBig bitmap!\n");

	spriteSpeed = al_load_bitmap("assets/speed.png");
	if (!spriteSpeed)
		fprintf(stderr, "failed to create spriteSpeed bitmap!\n");

	spriteInvul = al_load_bitmap("assets/invul.png");
	if (!spriteInvul)
		fprintf(stderr, "failed to create spriteInvul bitmap!\n");

	spriteLives = al_load_bitmap("assets/lives.png");
	if (!spriteLives)
		fprintf(stderr, "failed to create spriteLives bitmap!\n");
	powerUpSound = al_load_sample("assets/powerUpSound.wav");
	if (!powerUpSound) {
		fprintf(stderr, "Audio clip sample not loaded!\n");
		al_reserve_samples(1);
	}
}
PowerUp::~PowerUp()
{
	al_destroy_bitmap(spriteBig);
	al_destroy_bitmap(spriteSpeed);
	al_destroy_bitmap(spriteInvul);
	al_destroy_bitmap(spriteLives);
}
void PowerUp::ActivePower(Player* &p)
{
	al_stop_samples();
	al_play_sample(powerUpSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &powerUpID);
	switch (typePower)
	{
	case BIGBULLET:
		p->BiggerBullet();
		break;
	case SPEED:
		p->MoreSpeed();
		break;
	case INVUL:
		p->SetInvulnerable(true);
		break;
	case LIVES:
		p->AddLives(1);
		break;	
	}
	alive = false;
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
void PowerUp::Draw() const
{		
	if (alive)
	{
		switch (typePower)
		{			
		case BIGBULLET:
			al_draw_bitmap(spriteBig, x, y, 0);
			break;
		case SPEED:
			al_draw_bitmap(spriteSpeed, x, y, 0);
			break;
		case INVUL:
			al_draw_bitmap(spriteInvul, x, y, 0);
			break;
		case LIVES:
			al_draw_bitmap(spriteLives, x, y, 0);
			break;
		}
	}	
}
void PowerUp::Spawn()
{
	x = rand() % (screenWidth - width);
	y = rand() % (screenHeight - height);
	typePower = typeOfPower(rand()% LAST);
	std::cout << typePower;
	alive = true;
}

bool PowerUp::Alive()
{
	if (alive)
		return true;
	else
		return false;
}