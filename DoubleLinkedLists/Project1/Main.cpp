/*----------------------------
	File Name: Main.cpp
	Purpose: Run the program.
	Author: Logan Ryan
	Modified: 26/06/2020
------------------------------
	Copyright 2020 Logan Ryan.
----------------------------*/

#include <iostream>
#include "Game.h"
#include "DoubleLinkedList.h"

int main(int argc, char* argv[])
{


	DoubleLinkedList list;
	list.pushBack(10);
	list.pushFront(20);
	list.pushFront(30);
	list.popFront();
	list.insertAfter(list.begin()->next, 12);
	list.pushBack(10);
	list.sort();

	node* current = list.begin();
	while (current != nullptr )
	{
		std::cout << current->data << std::endl;
		current = current->next;
	}

	system("pause");

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