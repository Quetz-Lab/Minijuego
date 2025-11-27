/**
 * @file main.cpp
 * @brief Entry point for the interactive story game "La Torre del Mago"
 * 
 * Initializes the game, handles top-level error catching, and runs the main game loop.
 */

#include <iostream>
#include "Game.h"

int main()
{
	try
	{
		Game game;
		
		// Initialize the game (load story and resources)
		if (!game.Initialize())
		{
			std::cerr << "Error: No se pudo inicializar el juego" << std::endl;
			return 1;
		}
		
		// Run the main game loop
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error en el juego: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
