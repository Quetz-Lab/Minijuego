// Minijuego.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "RendeerManager.h"

#include <iostream>
#include "SkillList.h"

int main()
{
    SkillList skills;

    // 5 habilidades de ejemplo (las podemos renombrar y adaptar a nuestra historia)
    skills.AddSkill("Fireball");
    skills.AddSkill("Ice Spike");
    skills.AddSkill("Shadow Step");
    skills.AddSkill("Healing Aura");
    skills.AddSkill("Lightning Strike");

    std::cout << std::endl;
    std::cout << "Lista inicial de habilidades:" << std::endl;
    skills.Show();

    std::cout << std::endl;
    skills.ReplaceSkillAt(2, "Poison Dagger");
    std::cout << std::endl;
    skills.Show();

    std::cout << std::endl;
    skills.DeleteSkillAt(1);
    std::cout << std::endl;
    skills.Show();


    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture texture;
    if (!texture.loadFromFile("imagen1.png"))
    {
        // error...
    }

    sf::Sprite sprite(texture);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(sprite);
      
        window.display();
    }

    return 0;
}

