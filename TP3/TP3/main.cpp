#include <stdio.h>
#include "Game.h"
#ifdef DEBUG
#include "vld.h"
#endif

int main(int argc, char **argv)
{
	Game* game = new Game();
	if (game->InitAll())
	{
		game->MainMenu();
		game->UpdateGame();
		game->FinalMenu();
	}
	delete game;
}

