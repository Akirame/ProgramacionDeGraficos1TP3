#ifndef ENEMY_H
#define ENEMY_H
#include "allegro5\allegro.h"
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <ctime>

enum directions {
	ENEMY_UP,
	ENEMY_UP_LEFT,
	ENEMY_UP_RIGHT,
	ENEMY_LEFT,
	ENEMY_RIGHT,
	ENEMY_DOWN,
	ENEMY_DOWN_LEFT,
	ENEMY_DOWN_RIGHT,
	ENEMY_LAST
};
class Enemy {
private:
	int width;
	int height;
	int screenWidth;
	int screenHeight;
	directions touchUp[3] = {ENEMY_DOWN,ENEMY_DOWN_LEFT,ENEMY_DOWN_RIGHT};
	directions touchDown[3] = {ENEMY_UP,ENEMY_UP_LEFT,ENEMY_UP_RIGHT};
	directions touchLeft[3] = {ENEMY_UP_RIGHT,ENEMY_RIGHT,ENEMY_DOWN_RIGHT };
	directions touchRight[3] = {ENEMY_UP_LEFT,ENEMY_LEFT,ENEMY_DOWN_LEFT };
	directions startPos[4] = { ENEMY_UP,ENEMY_DOWN,ENEMY_LEFT,ENEMY_RIGHT };
	float x;
	float y;
	float speed;
	directions dir;
	ALLEGRO_BITMAP* sprite = NULL;
	void RandomDirOnTouch(directions dir[]);
public:
	Enemy(int screenWidth, int screenHeight,int startX,int startY);
	~Enemy();
	void SetX(float _x);
	void SetY(float _y);
	float GetX() const;
	float GetY() const;
	float GetHeight() const;
	float GetWidht() const;
	float GetSpeed() const;
	ALLEGRO_BITMAP* GetBitmap();
	void Movement(ALLEGRO_EVENT ev);
	void OOB();
	void Update(ALLEGRO_EVENT ev);
	void Draw() const;
	void Reset();
	void RandomPoint();
	void RandomDir();
	void speedPlusPlus();
};
#endif

