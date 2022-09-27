#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "../misc/Log.h"

namespace nema
{
    /**
     * Class that defines the GUI functionality
     * Uses imgui and is drawn on top of the basic SFML stuff
     */
    class GUI
    {
    public:
        GUI(sf::RenderWindow& window, sf::Time& dt, Log& log,
            sf::Texture& texture, std::mutex& mutex)
            : m_window(window), m_dt(dt), m_bShowMainMenuBar(true),
              m_bShowAppLog(true), m_appLog(log),
              m_hubballiFont(), m_currentTexture(texture),
              m_textureMutex(mutex), m_bShowSerial(false), m_bShowMotors(true)
        {
        }

        /**
         * Initializes imgui-SFML
         */
        void Init();

        /**
         * Updates the GUI each frame
         */
        void Update();

        /**
         * Renders the GUI
         */
        void Render();

        /**
         * Shuts down imgui-SFML
         */
        void Shutdown();

    private:
        /**
         * Handles imgui-SFML events like buttons and keyboard and mouse events
         */
        void PollEvents();

        /**
         * Draws the main menu bar at the top of the window
         */
        void ShowMainMenuBar();

        /**
         * Draws log with all the application output
         */
        void ShowAppLog();

        /**
         * Draws serial port control window
         */
        void ShowSerialPort();

        void ShowMotorControls();

        /**
         * Helper to display a little (?) mark which shows a tooltip when hovered.
         *
         * @param desc CString to display
         */
        static void HelpMarker(const char* desc)
        {
            ImGui::TextDisabled("(?)");
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted(desc);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
        }

        /**
         * Custom ImGui Combo overload that takes a vector of strings
         */
        bool Combo(const char* label, int* current_item,
                   const std::vector<std::string>& items, int items_count,
                   int height_in_items = -1)
        {
            return ImGui::Combo(
                    label, current_item,
                    [](void* data, int idx, const char** out_text)
                    {
                        *out_text =
                                (*(const std::vector<std::string>*) data)[idx]
                                        .c_str();
                        return true;
                    },
                    (void*) &items, items_count, height_in_items);
        }

        /// Reference to the SFML render window
        sf::RenderWindow& m_window;
        /// Delta time last frame
        sf::Time& m_dt;

        /// Reference to the SFML texture that is to be drawn this frame
        sf::Texture& m_currentTexture;
        /// Mutex for texture synchronisation
        std::mutex& m_textureMutex;

        /// Queue with recent frame times
        std::queue<float> m_frameTimeQueue;

        /// Reference to the app log
        Log& m_appLog;

        /// Pointer to a fancy font
        ImFont* m_hubballiFont;

        bool m_bShowMainMenuBar;
        bool m_bShowAppLog;
        bool m_bShowSerial;
        bool m_bShowMotors;

        /// Width for input fields in the GUI
        const uint16_t m_inputFieldWidth = 150;
        const std::string FONT_PATH = "./resources/fonts/hubballi-regular.ttf";

        /// Size of the queue that stores recent frame times
        const uint16_t FRAME_QUEUE_SIZE = 60;
    };
}// namespace nema