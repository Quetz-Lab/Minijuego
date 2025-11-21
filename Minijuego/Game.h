#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include <string>
#include "StoryManager.h"
#include "SkillList.h"
#include "RendeerManager.h"

class Game
{
public:
    Game();
    void Run();

private:
    // Core
    sf::RenderWindow m_window;
    sf::Clock        m_clock;

    // Lógica
    StoryManager     m_story;
    SkillList        m_skills;
    RendeerManager    m_renderManager;

    // UI
    sf::Font                 m_font;
    std::vector<sf::Text>    m_textLines;

    // Métodos internos
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();

    void RebuildTextsForCurrentNode();
    void HandleOptionSelection(int optionIndex);
};
