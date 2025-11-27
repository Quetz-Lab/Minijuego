#include "RenderManager.h"
#include "StoryNode.h"
#include "SkillList.h"
#include <iostream>

RenderManager::RenderManager(sf::RenderWindow& window)
    : m_window(window)
    , m_currentSprite(m_currentTexture)
    , m_hoveredOptionIndex(-1)
{
}

RenderManager::~RenderManager()
{
    // SFML resources (m_font, m_currentTexture, m_currentSprite) are
    // automatically cleaned up by their destructors
    // No manual cleanup needed
}

bool RenderManager::Initialize()
{
    // Load the font from the assets directory
    const char* fontPath = "assets/Roboto-Regular.ttf";
    
    if (!m_font.openFromFile(fontPath))
    {
        std::cerr << "Error: No se pudo cargar la fuente Roboto-Regular.ttf" << std::endl;
        return false;
    }
    
    return true;
}

void RenderManager::Clear(const sf::Color& color)
{
    // Clear the window with the specified color
    m_window.clear(color);
}

void RenderManager::Display()
{
    m_window.display();
}

void RenderManager::DrawText(const std::string& text, const sf::Vector2f& position,
                             unsigned int size, const sf::Color& color)
{
    sf::Text sfText(m_font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(position);
    m_window.draw(sfText);
}

void RenderManager::WrapText(const std::string& text, float maxWidth,
                             std::vector<std::string>& lines)
{
    lines.clear();
    
    if (text.empty())
    {
        return;
    }

    // Create a temporary text object for measuring line widths
    sf::Text tempText(m_font);
    tempText.setCharacterSize(20);  // Use standard size for measuring

    std::string currentLine;
    std::string word;
    
    // Process text character by character to build wrapped lines
    for (size_t i = 0; i < text.length(); ++i)
    {
        char c = text[i];
        
        // Word boundary detection: space, newline, or end of string
        if (c == ' ' || c == '\n' || i == text.length() - 1)
        {
            // Add last character if it's not a space or newline
            if (i == text.length() - 1 && c != ' ' && c != '\n')
            {
                word += c;
            }
            
            // Test if adding this word would exceed max width
            std::string testLine = currentLine;
            if (!testLine.empty())
            {
                testLine += " ";
            }
            testLine += word;
            
            tempText.setString(testLine);
            float width = tempText.getLocalBounds().size.x;
            
            // If line would be too long and we have content, wrap to new line
            if (width > maxWidth && !currentLine.empty())
            {
                lines.push_back(currentLine);
                currentLine = word;
            }
            else
            {
                currentLine = testLine;
            }
            
            // Handle explicit newline characters
            if (c == '\n')
            {
                lines.push_back(currentLine);
                currentLine.clear();
            }
            
            word.clear();
        }
        else
        {
            word += c;
        }
    }
    
    // Add the last line if not empty
    if (!currentLine.empty())
    {
        lines.push_back(currentLine);
    }
}

void RenderManager::DrawStoryNode(const StoryNode* node)
{
    if (!node)
    {
        return;
    }

    // Clear previous option bounds for hover detection
    m_optionBounds.clear();

    // Layout constants for positioning UI elements
    float leftMargin = 60.0f;
    float topMargin = 40.0f;
    float maxTextWidth = m_window.getSize().x - leftMargin - 280.0f;  // Leave space for skills panel
    float currentY = topMargin;

    // Draw title with improved styling - larger, golden color
    sf::Color titleColor(255, 215, 0);  // Gold
    DrawText(node->title, sf::Vector2f(leftMargin, currentY), 38, titleColor);
    currentY += 60.0f;

    // Draw main text with wrapping - improved readability with light gray
    std::vector<std::string> wrappedLines;
    WrapText(node->text, maxTextWidth, wrappedLines);
    
    sf::Color textColor(220, 220, 220);  // Light gray for better readability
    for (const auto& line : wrappedLines)
    {
        DrawText(line, sf::Vector2f(leftMargin, currentY), 22, textColor);
        currentY += 32.0f;
    }

    currentY += 30.0f;  // More space before options

    // Draw ending text if this is an ending node
    if (node->isEnding && !node->endingText.empty())
    {
        std::vector<std::string> endingLines;
        WrapText(node->endingText, maxTextWidth, endingLines);
        
        sf::Color endingColor(100, 200, 255);  // Light blue
        for (const auto& line : endingLines)
        {
            DrawText(line, sf::Vector2f(leftMargin, currentY), 22, endingColor);
            currentY += 32.0f;
        }
        
        currentY += 30.0f;
    }

    // Draw options with interactive hover highlighting
    if (node->HasOptions())
    {
        sf::Color optionsHeaderColor(120, 255, 120);  // Bright green
        DrawText("Opciones:", sf::Vector2f(leftMargin, currentY), 26, optionsHeaderColor);
        currentY += 45.0f;

        // Get current mouse position for real-time hover detection
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Render each option with hover effects
        for (size_t i = 0; i < node->options.size(); ++i)
        {
            const auto& option = node->options[i];
            std::string optionText = option.id + ") " + option.text;
            
            // Create temporary text to calculate bounds
            sf::Text tempText(m_font);
            tempText.setString(optionText);
            tempText.setCharacterSize(22);
            tempText.setPosition({leftMargin + 10.0f, currentY});
            
            // Store bounds for hover detection with padding for better UX
            sf::FloatRect bounds = tempText.getGlobalBounds();
            bounds.position.x -= 5.0f;
            bounds.position.y -= 3.0f;
            bounds.size.x += 10.0f;
            bounds.size.y += 6.0f;
            m_optionBounds.push_back(bounds);
            
            // Check if mouse is hovering over this option
            bool isHovered = bounds.contains(mousePosF);
            
            // Draw background highlight for hovered option
            if (isHovered)
            {
                sf::RectangleShape highlight;
                highlight.setPosition({bounds.position.x, bounds.position.y});
                highlight.setSize({bounds.size.x, bounds.size.y});
                highlight.setFillColor(sf::Color(60, 80, 120, 180));  // Semi-transparent blue
                m_window.draw(highlight);
            }
            
            // Choose text color based on hover state (brighter when hovered)
            sf::Color optionColor = isHovered ? sf::Color(255, 255, 150) : sf::Color(200, 200, 200);
            
            DrawText(optionText, sf::Vector2f(leftMargin + 10.0f, currentY), 22, optionColor);
            currentY += 40.0f;
        }
    }
}

int RenderManager::GetHoveredOption(const sf::Vector2i& mousePos) const
{
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    for (size_t i = 0; i < m_optionBounds.size(); ++i)
    {
        if (m_optionBounds[i].contains(mousePosF))
        {
            return static_cast<int>(i);
        }
    }
    
    return -1;  // No option is hovered
}

void RenderManager::DrawNodeImage(const std::string& imagePath)
{
    if (imagePath.empty())
    {
        return;
    }

    // Texture caching: only reload if the image path has changed
    if (imagePath != m_currentImagePath)
    {
        if (!m_currentTexture.loadFromFile(imagePath))
        {
            std::cerr << "Warning: No se pudo cargar la imagen: " << imagePath << std::endl;
            m_currentImagePath.clear();
            return;
        }
        m_currentImagePath = imagePath;
        m_currentSprite = sf::Sprite(m_currentTexture);
    }

    // Define the display area (right side of window, top portion)
    float displayX = m_window.getSize().x - 280.0f;
    float displayY = 40.0f;
    float maxWidth = 260.0f;
    float maxHeight = 280.0f;

    // Draw a decorative frame/border around the image area
    sf::RectangleShape frame;
    frame.setPosition({displayX - 5.0f, displayY - 5.0f});
    frame.setSize({maxWidth + 10.0f, maxHeight + 10.0f});
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color(100, 120, 150, 255));  // Subtle border
    frame.setOutlineThickness(3.0f);
    m_window.draw(frame);

    // Get original image dimensions for scaling calculations
    sf::Vector2u imageSize = m_currentTexture.getSize();
    float imageWidth = static_cast<float>(imageSize.x);
    float imageHeight = static_cast<float>(imageSize.y);

    // Calculate proportional scaling to fit within display area while maintaining aspect ratio
    float scaleX = maxWidth / imageWidth;
    float scaleY = maxHeight / imageHeight;
    float scale = std::min(scaleX, scaleY);  // Use the smaller scale to ensure both dimensions fit

    // Center the scaled image within the display area
    float scaledWidth = imageWidth * scale;
    float scaledHeight = imageHeight * scale;
    float centerX = displayX + (maxWidth - scaledWidth) / 2.0f;
    float centerY = displayY + (maxHeight - scaledHeight) / 2.0f;

    m_currentSprite.setScale({scale, scale});
    m_currentSprite.setPosition({centerX, centerY});

    m_window.draw(m_currentSprite);
}

void RenderManager::DrawSkillList(const SkillList& skills)
{
    // Position skill list on the right side, below the image area
    float skillX = m_window.getSize().x - 280.0f;
    float skillY = 360.0f;
    float panelWidth = 260.0f;

    // Draw a subtle background panel for the skills section
    sf::RectangleShape panel;
    panel.setPosition({skillX - 10.0f, skillY - 10.0f});
    
    // Calculate panel height based on number of skills
    int count = skills.Count();
    float panelHeight = 80.0f + (count * 32.0f);
    panel.setSize({panelWidth, panelHeight});
    panel.setFillColor(sf::Color(40, 45, 60, 200));  // Semi-transparent dark panel
    panel.setOutlineColor(sf::Color(100, 120, 150, 255));  // Subtle border
    panel.setOutlineThickness(2.0f);
    m_window.draw(panel);

    // Draw section header
    sf::Color headerColor(255, 150, 255);  // Bright magenta/pink
    DrawText("Habilidades:", sf::Vector2f(skillX, skillY), 26, headerColor);
    skillY += 45.0f;

    // Draw each skill with its index (1-based for user display)
    sf::Color skillColor(180, 220, 255);  // Light cyan
    for (int i = 0; i < count; ++i)
    {
        std::string skillText = std::to_string(i + 1) + ". " + skills.GetSkillAt(i);
        DrawText(skillText, sf::Vector2f(skillX + 5.0f, skillY), 19, skillColor);
        skillY += 32.0f;
    }
}
