#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Forward declarations
class StoryNode;
class SkillList;

/**
 * @class RenderManager
 * @brief Handles all visual rendering for the game
 * 
 * Manages drawing of story text, images, UI elements, and skill lists.
 * Implements text wrapping, image scaling, and interactive hover effects.
 * Maintains separation between rendering logic and game logic.
 */
class RenderManager
{
public:
    RenderManager(sf::RenderWindow& window);
    ~RenderManager();

    // Initialize resources (fonts, textures)
    bool Initialize();

    // Draw the current story node
    void DrawStoryNode(const StoryNode* node);

    // Draw the skill list
    void DrawSkillList(const SkillList& skills);

    // Draw an image associated with the node
    void DrawNodeImage(const std::string& imagePath);

    // Clear the screen
    void Clear(const sf::Color& color = sf::Color::Black);

    // Display what has been drawn
    void Display();

    // Get the index of the option under the mouse (-1 if none)
    int GetHoveredOption(const sf::Vector2i& mousePos) const;

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Texture m_currentTexture;
    sf::Sprite m_currentSprite;
    std::string m_currentImagePath;  // Track current image to avoid reloading

    std::vector<sf::FloatRect> m_optionBounds;  // For hover detection
    int m_hoveredOptionIndex;  // Track which option is currently hovered

    // Private helper methods
    void DrawText(const std::string& text, const sf::Vector2f& position,
                  unsigned int size, const sf::Color& color);
    void WrapText(const std::string& text, float maxWidth,
                  std::vector<std::string>& lines);
};
