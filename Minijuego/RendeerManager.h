#pragma once
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

class RendeerManager
{
public:

	list<sf::RectangleShape> shapesToRender;
	
	RendeerManager() {};

	void AddShapeToList(sf::RectangleShape shape) {
		shapesToRender.push_back(shape);
	}

	void Draw(sf::RenderWindow &window)
	{
		for(sf::RectangleShape shape : shapesToRender)
		{
			window.draw(shape);
		}
	}
};

