#include <iostream>
#include "Game.h"

int main()
{
	try
	{
		Game game;
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Errror eneljuego"
			<< e.what() << std::endl;
	}
	return 0;
}