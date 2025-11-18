// Minijuego.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "RendeerManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");

    RendeerManager renderManager;

    sf::RectangleShape shape({ 200, 200 });

    renderManager.AddShapeToList(shape);


    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        renderManager.Draw(window);
        window.display();
    }
}
