/*----------------------------
	File Name: Main.cpp
	Purpose: Run the program.
	Author: Logan Ryan
	Modified: 26/06/2020
------------------------------
	Copyright 2020 Logan Ryan.
----------------------------*/

#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;

	game.initialisation();

	// Main game loop
	while (!game.isWindowClosed())
	{
		game.update();

		game.draw();
	}

	return 0;
}