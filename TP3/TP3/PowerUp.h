#ifndef POWERUP_H
#define POWERUP_H
#include "allegro5\allegro.h"
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <ctime>
#include "Player.h"

enum typeOfPower 
{
	BIG,
	SPEED,
	INVUL,
	LIVES,
	LAST
};
class PowerUp {
private:
	int width;
	int height;
	int screenWidth;
	int screenHeight;
	float x;
	float y;
	ALLEGRO_BITMAP* sprite = NULL;
	typeOfPower typePower;
public:
	PowerUp(int screenWidth, int screenHeight);
	~PowerUp();
	void SetX(float _x);
	void SetY(float _y);
	float GetX() const;
	float GetY() const;
	float GetHeight() const;
	float GetWidht() const;	
	typeOfPower GetType() const;
	ALLEGRO_BITMAP* GetBitmap();
	void ActivePower(Player &p);
};
#endif
