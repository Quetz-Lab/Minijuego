#pragma once

#include <SFML/Graphics.hpp>

/**
 * @class InputManager
 * @brief Handles all user input processing
 * 
 * Processes SFML events including mouse clicks, keyboard input, and window events.
 * Maintains frame-specific input state that is reset each frame to ensure
 * proper event handling in the game loop.
 */
class InputManager {
public:
    InputManager(sf::RenderWindow& window);
    
    // Procesa todos los eventos pendientes
    void ProcessEvents();
    
    // Verifica si se solicitó cerrar la ventana
    bool ShouldClose() const;
    
    // Obtiene la posición del mouse
    sf::Vector2i GetMousePosition() const;
    
    // Verifica si se hizo click izquierdo este frame
    bool WasLeftClicked() const;
    
    // Verifica si se presionó Escape
    bool WasEscapePressed() const;
    
    // Resetea el estado del frame
    void ResetFrameState();
    
private:
    sf::RenderWindow& m_window;
    bool m_shouldClose;
    bool m_leftClicked;
    bool m_escapePressed;
};
