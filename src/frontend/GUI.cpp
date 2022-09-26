#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <range/v3/all.hpp>

#include "../utils/MySerial.h"
#include "GUI.h"

//TODO Disabled blocks
namespace nema
{
    void GUI::Init()
    {
        spdlog::debug("GUI Init started");
        ImGui::SFML::Init(m_window);

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        m_hubballiFont = io.Fonts->AddFontFromFileTTF(FONT_PATH.c_str(), 20);
        ImGui::SFML::UpdateFontTexture();
        spdlog::debug("Font loaded from {}", FONT_PATH);

        ImGui::GetStyle().FrameRounding = 4.0f;
        ImGui::GetStyle().GrabRounding = 4.0f;

        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] =
                ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] =
                ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] =
                ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] =
                ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] =
                ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        spdlog::debug("GUI Init successful");
    }

    void GUI::PollEvents()
    {
        sf::Event event{};

        while (m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            m_window.close();
                            break;
                        case sf::Keyboard::LAlt:
                            m_bShowMainMenuBar = !m_bShowMainMenuBar;
                            break;
                        case sf::Keyboard::F1:
                            m_bShowVideoProcessor = !m_bShowVideoProcessor;
                            break;
                        case sf::Keyboard::F2:
                            m_bShowFrameInfoOverlay = !m_bShowFrameInfoOverlay;
                            break;
                        case sf::Keyboard::F3:
                            m_bShowImageViewer = !m_bShowImageViewer;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void GUI::Update()
    {
        PollEvents();
        ImGui::SFML::Update(m_window, m_dt);

        m_frameTimeQueue.push(static_cast<float>(m_dt.asMicroseconds()));
        if (m_frameTimeQueue.size() > FRAME_QUEUE_SIZE)
        {
            m_frameTimeQueue.pop();
        }
    }

    void GUI::ShowFrameInfoOverlay()
    {
        static int corner = 1;
        auto window_flags = ImGuiWindowFlags_NoDecoration |
                            ImGuiWindowFlags_AlwaysAutoResize |
                            ImGuiWindowFlags_NoSavedSettings |
                            ImGuiWindowFlags_NoFocusOnAppearing |
                            ImGuiWindowFlags_NoNav;
        if (corner != -1)
        {
            const auto PAD = 10.0f;
            const auto* viewport = ImGui::GetMainViewport();
            auto work_pos =
                    viewport->WorkPos;// Use work area to avoid menu-bar/task-bar, if any!
            auto work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD)
                                        : (work_pos.x + PAD);
            window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD)
                                        : (work_pos.y + PAD);
            window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always,
                                    window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f);// Transparent background
        if (ImGui::Begin("FrameInfoOverlay", &m_bShowFrameInfoOverlay,
                         window_flags))
        {
            ImGui::Text("Frame info");
            ImGui::Separator();
            ImGui::Text("Frametime: %d ms\nFPS: %.3f", m_dt.asMilliseconds(),
                        1.f / m_dt.asSeconds());
            ImGui::PlotLines("Frame Times", &m_frameTimeQueue.front(),
                             static_cast<int>(m_frameTimeQueue.size()), 0,
                             nullptr, FLT_MAX, FLT_MAX, ImVec2{100, 40});

            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Custom", nullptr, corner == -1))
                    corner = -1;
                if (ImGui::MenuItem("Top-left", nullptr, corner == 0))
                    corner = 0;
                if (ImGui::MenuItem("Top-right", nullptr, corner == 1))
                    corner = 1;
                if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2))
                    corner = 2;
                if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3))
                    corner = 3;
                if (ImGui::MenuItem("Close")) m_bShowFrameInfoOverlay = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    void GUI::ShowMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Windows"))
            {
                if (ImGui::MenuItem("Viewport", nullptr, &m_bShowViewport)) {}
                if (ImGui::MenuItem("Frame Info", "F2",
                                    &m_bShowFrameInfoOverlay))
                {
                }
                if (ImGui::MenuItem("Serial Controller", nullptr,
                                    &m_bShowSerial))
                {
                }
                if (ImGui::MenuItem("App Log", nullptr, &m_bShowAppLog)) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Show Help", nullptr, &m_bShowHelp)) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void GUI::ShowViewport()
    {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_HorizontalScrollbar;
        if (ImGui::Begin("Viewport", &m_bShowViewport, windowFlags))
        {
            std::scoped_lock lock{m_textureMutex};
            ImGui::Image(m_currentTexture);
        }
        ImGui::End();
    }

    void GUI::ShowAppLog()
    {
        // For the demo: add a debug button _BEFORE_ the normal log window contents
        // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
        // Most of the contents of the window will be added by the log.Draw() call.

        ImGui::Begin("App Log", &m_bShowAppLog);
        ImGui::End();

        // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
        m_appLog.Draw("App Log", &m_bShowAppLog);
    }

    void GUI::Render()
    {
        ImGui::PushFont(m_hubballiFont);
        ImGui::DockSpaceOverViewport();

        if (m_bShowMainMenuBar) ShowMainMenuBar();
        if (m_bShowViewport) ShowViewport();
        if (m_bShowFrameInfoOverlay) ShowFrameInfoOverlay();
        if (m_bShowAppLog) ShowAppLog();
        if (m_bShowSerial) ShowSerialPort();

#ifndef NDEBUG
        ImGui::ShowDemoWindow();
#endif

        ImGui::PopFont();
        ImGui::SFML::Render(m_window);
    }

    void GUI::Shutdown() { ImGui::SFML::Shutdown(); }

    void GUI::ShowSerialPort()
    {
        if (ImGui::Begin("Serial Controller", &m_bShowImageViewer))
        {
            ULONG size = 10;
            std::vector<ULONG> coms(size);
            ULONG found = 0;

            GetCommPorts(coms.data(), size, &found);
            ::ranges::sort(coms.begin(), coms.end());
            auto portStrs = coms |
                            ::ranges::views::filter([](auto comNum)
                                                    { return comNum != 0; }) |
                            ::ranges::views::transform(
                                    [](auto comNum)
                                    { return fmt::format("COM{}", comNum); }) |
                            ::ranges::to<std::vector<std::string>>();

            /*
            static SimpleSerial serial(
                    (char*) fmt::format("\\\\.\\{}",
                                        portStrs[portStrs.size() - 1])
                            .c_str(),
                    CBR_9600);
                    */
            static MySerial serial(
                    fmt::format("\\\\.\\{}", portStrs[portStrs.size() - 1]),
                    CBR_9600);

            static int currentPort = portStrs.size() - 1;
            ImGui::PushItemWidth(m_inputFieldWidth);
            Combo("Port", &currentPort, portStrs, portStrs.size());

            ImGui::SameLine();
            if (ImGui::Button("Connect"))
            {
                serial.Connect(
                        fmt::format("\\\\.\\{}", portStrs[portStrs.size() - 1]),
                        CBR_9600);

                if (serial.IsConnected())
                {
                    spdlog::info("Connected to {} successfully",
                                 portStrs[currentPort]);
                }
                else
                {
                    spdlog::error("Couldn't connect to {}",
                                  portStrs[currentPort]);
                }

                spdlog::info("{}", serial.ReadSerialPort(100, 1));
            }

            static std::string toSend{};
            ImGui::InputTextWithHint("Send to serial port", nullptr, &toSend);
            if (ImGui::IsItemDeactivatedAfterEdit() && !toSend.empty())
            {
                spdlog::info("{}", serial.IsConnected());
                if (serial.WriteSerialPort(toSend))
                {
                    spdlog::info("Sent \"{}\"\nReceived {}", toSend,
                                 serial.ReadSerialPort(100, 1));
                }
                else
                {
                    spdlog::error("Couldn't send string");
                }
            }
            ImGui::PopItemWidth();
        }
        ImGui::End();
    }
}// namespace nema