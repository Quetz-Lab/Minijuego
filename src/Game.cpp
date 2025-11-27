#include "Game.h"
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode({ 1280u, 720u }), "La Torre del Mago")
    , m_renderManager(m_window)
    , m_inputManager(m_window)
    , m_isRunning(false)
{
    // Set framerate limit to 60 FPS
    m_window.setFramerateLimit(60);
}

Game::~Game()
{
    // Cleanup is handled automatically by destructors of member objects:
    // - m_window: SFML handles cleanup
    // - m_storyManager: Cleans up story nodes map
    // - m_renderManager: SFML resources (font, texture) are cleaned up
    // - m_inputManager: No dynamic resources to clean
    // - m_skills: SkillList destructor calls Clear() to free all nodes
}

bool Game::Initialize()
{
    // Initialize RenderManager (load fonts)
    if (!m_renderManager.Initialize())
    {
        std::cerr << "Error: No se pudo inicializar RenderManager" << std::endl;
        return false;
    }
    
    // Load story from JSON
    if (!m_storyManager.LoadFromFile("assets/story.json"))
    {
        std::cerr << "Error: No se pudo cargar la historia desde assets/story.json" << std::endl;
        return false;
    }
    
    // Start at the beginning of the story
    m_storyManager.Start();
    
    // Add initial skills (thematic to the wizard story)
    m_skills.AddSkill("Círculo de Luz");
    m_skills.AddSkill("Sello de Runas");
    m_skills.AddSkill("Absorción de Tormenta");
    
    m_isRunning = true;
    return true;
}

void Game::Run()
{
    if (!m_isRunning)
    {
        std::cerr << "Error: Game no está inicializado. Llama a Initialize() primero." << std::endl;
        return;
    }
    
    while (m_window.isOpen() && m_isRunning)
    {
        HandleInput();
        Update();
        Render();
    }
}

void Game::HandleInput()
{
    // Reset frame-specific input state before processing new events
    m_inputManager.ResetFrameState();
    
    // Process all pending SFML events from the event queue
    m_inputManager.ProcessEvents();
    
    // Handle window close requests (X button or Escape key)
    if (m_inputManager.ShouldClose() || m_inputManager.WasEscapePressed())
    {
        m_window.close();
        m_isRunning = false;
        return;
    }
    
    // Handle mouse clicks on story options
    if (m_inputManager.WasLeftClicked())
    {
        sf::Vector2i mousePos = m_inputManager.GetMousePosition();
        int hoveredOption = m_renderManager.GetHoveredOption(mousePos);
        
        // If mouse is over a valid option, navigate to the next node
        if (hoveredOption >= 0)
        {
            const StoryNode* currentNode = m_storyManager.GetCurrentNode();
            
            // Validate that we can select an option (not at ending, valid index)
            if (currentNode && !currentNode->isEnding && hoveredOption < static_cast<int>(currentNode->options.size()))
            {
                const StoryOption& selectedOption = currentNode->options[hoveredOption];
                
                // Attempt to navigate to the next node via the selected option
                if (!m_storyManager.SelectOption(selectedOption.id))
                {
                    std::cerr << "Error: No se pudo seleccionar la opción " << selectedOption.id << std::endl;
                }
            }
        }
    }
}

void Game::Update()
{
    // Check if we've reached an ending
    if (m_storyManager.IsAtEnding())
    {
        // At an ending node - no further updates needed
        // Player can only press Escape to exit
    }
    
    // Future: Update skill states, animations, etc.
}

void Game::Render()
{
    // Clear the screen with a dark blue-gray background
    m_renderManager.Clear(sf::Color(20, 20, 35));
    
    // Get the current story node to render
    const StoryNode* currentNode = m_storyManager.GetCurrentNode();
    
    // Draw the node's associated image if it exists
    // Convention: node ID maps to image filename (e.g., "n1" -> "assets/n1.png")
    if (currentNode && !currentNode->id.empty())
    {
        std::string imagePath = "assets/" + currentNode->id + ".png";
        m_renderManager.DrawNodeImage(imagePath);
    }
    
    // Draw the main story content (title, text, and player options)
    m_renderManager.DrawStoryNode(currentNode);
    
    // Draw the player's skill list in the side panel
    m_renderManager.DrawSkillList(m_skills);
    
    // Present the rendered frame to the window
    m_renderManager.Display();
}
