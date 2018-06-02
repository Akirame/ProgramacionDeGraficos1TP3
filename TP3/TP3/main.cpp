#include <stdio.h>
#include "Game.h"

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

