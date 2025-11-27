#pragma once

#include "SFML/Graphics.hpp"
#include "StoryManager.h"
#include "SkillList.h"
#include "RenderManager.h"
#include "InputManager.h"

/**
 * @class Game
 * @brief Main game controller that coordinates all game systems
 * 
 * The Game class manages the main game loop and coordinates between
 * the story system, rendering, input handling, and skill management.
 * It follows a standard game loop pattern: Input -> Update -> Render.
 */
class Game
{
public:
    Game();
    ~Game();
    
    // Initialize the game (load story and resources)
    bool Initialize();
    
    // Run the main game loop
    void Run();

private:
    // SFML Window
    sf::RenderWindow m_window;
    
    // Game Components
    StoryManager m_storyManager;
    RenderManager m_renderManager;
    InputManager m_inputManager;
    SkillList m_skills;
    
    // Game state
    bool m_isRunning;
    
    // Internal methods
    void HandleInput();
    void Update();
    void Render();
};
