#include "PowerUp.h"

PowerUp::PowerUp(int _screenWidth, int _screenHeight) : screenWidth(_screenWidth), screenHeight(_screenHeight),alive(false)
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
			al_draw_bitmap(spriteInvul, x, y, 0);
			break;
		}
	}	
}
void PowerUp::Spawn()
{
	x = rand() % (screenWidth - width);
	y = rand() % (screenHeight - height);
	typePower = typeOfPower(rand()% LAST);
	alive = true;
}

bool PowerUp::Alive()
{
	if (alive)
		return true;
	else
		return false;
}