#include "Game.h"
#include <iostream>

Game::Game()
sf::RenderWindow window(sf::VideoMode({1280, 720 }), "Minijuego - Eldrin y la Tormenta")
{
    m_window.setFramerateLimit(60);

    // Cargar fuente 
    if (!m_font.loadFromFile("assets/Roboto-Regular.ttf"))
    {
        std::cerr << "No se pudo cargar la fuente. Asegúrate de tener assets/Roboto-Regular.ttf\n";
    }

    // Cargar historia
    if (!m_story.LoadFromFile("story.json"))
    {
        std::cerr << "No se pudo cargar story.json\n";
    }

    // Configurar texto inicial
    RebuildTextsForCurrentNode();
}

void Game::Run()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();
        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

void Game::ProcessEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Num1) HandleOptionSelection(0);
            if (event.key.code == sf::Keyboard::Num2) HandleOptionSelection(1);
            if (event.key.code == sf::Keyboard::Num3) HandleOptionSelection(2);
            if (event.key.code == sf::Keyboard::Num4) HandleOptionSelection(3);
        }
    }
}

void Game::Update(float deltaTime)
{
    // Por ahora no hay lógica de tiempo
    // Aquí se podra actualizar animaciones, timers, etc.
}

void Game::Render()
{
    m_window.clear(sf::Color(20, 20, 35));

    // Dibujar fondo simple con RenderManager (ejemplo)
    m_renderManager.Draw(m_window);

    // Dibujar textos
    for (const auto& t : m_textLines)
    {
        m_window.draw(t);
    }

    m_window.display();
}

void Game::RebuildTextsForCurrentNode()
{
    m_textLines.clear();

    const StoryNode* node = m_story.GetCurrentNode();
    if (!node)
    {
        // Mensaje de error visible
        sf::Text errorText;
        errorText.setFont(m_font);
        errorText.setString("No se pudo encontrar el nodo actual de la historia.");
        errorText.setCharacterSize(24);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(50.f, 50.f);
        m_textLines.push_back(errorText);
        return;
    }

    float x = 50.f;
    float y = 40.f;
    float lineSpacing = 36.f;

    // Título
    {
        sf::Text title;
        title.setFont(m_font);
        title.setString(node->title);
        title.setCharacterSize(32);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(x, y);
        m_textLines.push_back(title);
        y += lineSpacing * 1.5f;
    }

    // Texto principal
    {
        sf::Text body;
        body.setFont(m_font);
        body.setString(node->text);
        body.setCharacterSize(22);
        body.setFillColor(sf::Color::White);
        body.setPosition(x, y);
        m_textLines.push_back(body);
        y += lineSpacing * 3.f;
    }

    if (node->isEnding)
    {
        sf::Text ending;
        ending.setFont(m_font);
        ending.setString(node->textEnding + "\n\n(Ya llegaste a un final. Presiona ESC para cerrar la ventana.)");
        ending.setCharacterSize(20);
        ending.setFillColor(sf::Color(200, 200, 200));
        ending.setPosition(x, y);
        m_textLines.push_back(ending);
        return;
    }

    // Opciones
    int index = 1;
    for (const auto& opt : node->options)
    {
        sf::Text optText;
        optText.setFont(m_font);

        std::string line = std::to_string(index) + ") " + opt.text;
        optText.setString(line);

        optText.setCharacterSize(20);
        optText.setFillColor(sf::Color(180, 220, 180));
        optText.setPosition(x, y);
        m_textLines.push_back(optText);

        y += lineSpacing;
        ++index;
    }
}

void Game::HandleOptionSelection(int optionIndex)
{
    const StoryNode* node = m_story.GetCurrentNode();
    if (!node || node->isEnding) return;

    if (optionIndex < 0 || optionIndex >= static_cast<int>(node->options.size()))
        return;

    const StoryOption& opt = node->options[optionIndex];

    // Ejemplo: usamos la lista ligada para registrar una "decisión" como habilidad
    m_skills.AddSkill("Opcion " + opt.id + ": " + opt.text);

    bool ok = m_story.GoToNode(opt.nextNodeId);
    if (!ok)
    {
        std::cerr << "No se pudo ir al nodo con id: " << opt.nextNodeId << std::endl;
    }

    RebuildTextsForCurrentNode();
}
