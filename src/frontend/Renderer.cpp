#include "Renderer.h"

namespace nema
{
    void Renderer::Render() { m_window.clear(sf::Color::Black); }

    void Renderer::Display() { m_window.display(); }
}// namespace nema