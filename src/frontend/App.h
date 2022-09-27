#pragma once

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include "../misc/Log.h"
#include "GUI.h"
#include "Renderer.h"

namespace nema
{
    /**
     * Main application class that stores all the app data and runs the main app loop
     */
    class App
    {
    public:
        App(int argc, char** argv, uint16_t width, uint16_t height,
            const sf::ContextSettings& settings, Log& log)
            : m_window(sf::VideoMode{width, height}, "Nema App",
                       sf::Style::Default, settings),
              m_renderer(m_window),
              m_gui(m_window, m_dt, log, m_currentTexture, m_textureMutex)
        {
            sf::Image icon{};
            if (!icon.loadFromFile(ICON_PATH))
            {
                spdlog::error("Failed to load app icon");
            }
            else
            {
                m_window.setIcon(icon.getSize().x, icon.getSize().y,
                                 icon.getPixelsPtr());
                spdlog::debug("Successfully set iconf from {}", ICON_PATH);
            }
        }

        /**
         * Runs the main application loop, where each loop corresponds to one frame
         */
        void Run();

    private:
        /// SFML Render Window to draw the image to
        sf::RenderWindow m_window;

        /// SFML Clock that keeps track of app time
        sf::Clock m_deltaClock;
        /// Delta time last frame
        sf::Time m_dt;

        /// Renderer that draws all stuff to the window
        Renderer m_renderer;
        /// App GUI instance
        GUI m_gui;

        /// SFML Texture to draw on screen this frame
        sf::Texture m_currentTexture;
        /// mutex for texture synchronisation
        std::mutex m_textureMutex;

        const std::string ICON_PATH = "./resources/images/cam_icon.png";
    };
}// namespace nema