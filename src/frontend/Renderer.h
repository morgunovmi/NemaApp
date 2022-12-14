#pragma once

#include <SFML/Graphics.hpp>

namespace nema
{
    /**
     * Class for drawing stuff to the SFML window
     */
    class Renderer
    {
    public:
        Renderer(sf::RenderWindow& window) : m_window(window)
        {
            m_window.setFramerateLimit(60);
        }

        /**
         * Draws a texture to the SFML window each frame
         */
        void Render();

        /**
         * Displays everything drawn to the SFML window on the display
         */
        void Display();

    private:
        /// Reference to the SFML render window
        sf::RenderWindow& m_window;
    };
}// namespace nema