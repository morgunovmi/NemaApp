#include "App.h"
#include <spdlog/spdlog.h>

namespace nema
{
    void App::Run()
    {
        spdlog::debug("App::Run started");
        m_gui.Init();
        while (m_window.isOpen())
        {
            m_dt = m_deltaClock.restart();
            m_gui.Update();
            m_renderer.Render();
            m_gui.Render();
            m_renderer.Display();
        }
        m_gui.Shutdown();
    }
}// namespace nema