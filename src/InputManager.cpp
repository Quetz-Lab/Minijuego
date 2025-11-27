#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow& window)
    : m_window(window)
    , m_shouldClose(false)
    , m_leftClicked(false)
    , m_escapePressed(false)
{
}

void InputManager::ProcessEvents() {
    // Process all events in the queue
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_shouldClose = true;
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                m_escapePressed = true;
            }
        }
        else if (event->is<sf::Event::MouseButtonPressed>()) {
            const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>();
            if (mousePressed && mousePressed->button == sf::Mouse::Button::Left) {
                m_leftClicked = true;
            }
        }
    }
}

bool InputManager::ShouldClose() const {
    return m_shouldClose;
}

sf::Vector2i InputManager::GetMousePosition() const {
    return sf::Mouse::getPosition(m_window);
}

bool InputManager::WasLeftClicked() const {
    return m_leftClicked;
}

bool InputManager::WasEscapePressed() const {
    return m_escapePressed;
}

void InputManager::ResetFrameState() {
    m_leftClicked = false;
    m_escapePressed = false;
    // Note: m_shouldClose is not reset as it's a persistent state
}
