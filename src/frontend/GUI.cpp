#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <range/v3/all.hpp>

#include "../utils/MySerial.h"
#include "GUI.h"
#include "arduino/MyMotor.h"

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

    void GUI::ShowMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Windows"))
            {
                if (ImGui::MenuItem("Serial Controller", nullptr,
                                    &m_bShowSerial))
                {
                }
                if (ImGui::MenuItem("App Log", nullptr, &m_bShowAppLog)) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
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
        if (m_bShowAppLog) ShowAppLog();
        if (m_bShowSerial) ShowSerialPort();
        if (m_bShowMotors) ShowMotorControls();

#ifndef NDEBUG
        ImGui::ShowDemoWindow();
#endif

        ImGui::PopFont();
        ImGui::SFML::Render(m_window);
    }

    void GUI::Shutdown() { ImGui::SFML::Shutdown(); }

    void GUI::ShowSerialPort()
    {
        if (ImGui::Begin("Serial Controller", &m_bShowSerial))
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

                spdlog::info("{}", serial.ReadSerialPort());
            }

            static std::string toSend{};
            ImGui::InputTextWithHint("Send to serial port", nullptr, &toSend);
            if (ImGui::IsItemDeactivatedAfterEdit() && !toSend.empty())
            {
                if (serial.WriteSerialPort(toSend))
                {
                    spdlog::info("Sent \"{}\"\nReceived {}", toSend,
                                 serial.ReadSerialPort());
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

    void GUI::ShowMotorControls()
    {
        if (ImGui::Begin("Motor Controls", &m_bShowMotors))
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

            static MyMotor motor1{
                    fmt::format("\\\\.\\{}", portStrs[portStrs.size() - 2]),
                    CBR_9600};

            static MyMotor motor2{
                    fmt::format("\\\\.\\{}", portStrs[portStrs.size() - 1]),
                    CBR_9600};

            static int currentPort1 = portStrs.size() - 2;
            static int currentPort2 = portStrs.size() - 1;
            ImGui::PushItemWidth(m_inputFieldWidth);
            Combo("Motor 1 Port", &currentPort1, portStrs, portStrs.size());
            ImGui::SameLine();
            Combo("Motor 2 Port", &currentPort2, portStrs, portStrs.size());

            if (ImGui::Button("Connect 1"))
            {
                motor1.Connect(fmt::format("\\\\.\\{}", portStrs[currentPort1]),
                               CBR_9600);

                if (motor1.IsConnected())
                {
                    spdlog::info("Connected to {} successfully",
                                 portStrs[currentPort1]);
                }
                else
                {
                    spdlog::error("Couldn't connect to {}",
                                  portStrs[currentPort1]);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Connect 2"))
            {
                motor2.Connect(fmt::format("\\\\.\\{}", portStrs[currentPort2]),
                               CBR_9600);

                if (motor2.IsConnected())
                {
                    spdlog::info("Connected to {} successfully",
                                 portStrs[currentPort2]);
                }
                else
                {
                    spdlog::error("Couldn't connect to {}",
                                  portStrs[currentPort2]);
                }
            }

            HelpMarker("These coefficients are used to convert from "
                       "milliliters to motor steps\n"
                       "All amounts below are in milliliters");
            ImGui::DragFloat("vol to step coef 1", &motor1.m_volToStepCoef, 0.5,
                             5000, 15000);
            ImGui::SameLine();
            ImGui::DragFloat("vol to step coef 2", &motor2.m_volToStepCoef, 0.5,
                             5000, 15000);

            static float speed1 = 10.0;
            ImGui::DragFloat("Speed 1", &speed1, 0.5, 0, 30);
            ImGui::SameLine();
            static float speed2 = 10.0;
            ImGui::DragFloat("Speed 2", &speed2, 0.5, 0, 30);
            ImGui::SameLine();
            HelpMarker("milliliters per minute");

            static float amount1 = 0.1;
            ImGui::DragFloat("Amount 1", &amount1, 0.5, 0, 30);
            ImGui::SameLine();
            static float amount2 = 0.1;
            ImGui::DragFloat("Amount 2", &amount2, 0.5, 0, 30);
            ImGui::SameLine();
            HelpMarker("milliliters");

            if (ImGui::Button("Forward 1")) { motor1.Go(-amount1, speed1); }
            ImGui::SameLine();

            if (ImGui::Button("Forward 2")) { motor2.Go(amount2, speed2); }

            if (ImGui::Button("Back 1")) { motor1.Go(amount1, speed1); }
            ImGui::SameLine();

            if (ImGui::Button("Back 2")) { motor2.Go(-amount2, speed2); }

            if (ImGui::Button("Forward Both"))
            {
                motor1.Go(amount1, speed1);
                motor2.Go(amount2, speed2);
            }
            ImGui::SameLine();

            if (ImGui::Button("Back Both"))
            {
                motor1.Go(-amount1, speed1);
                motor2.Go(-amount2, speed2);
            }

            if (ImGui::Button("Stop 1")) { motor1.Stop(); }
            ImGui::SameLine();

            if (ImGui::Button("Stop 2")) { motor2.Stop(); }

            if (ImGui::Button("Stop both"))
            {
                motor1.Stop();
                motor2.Stop();
            }
        }
        ImGui::End();
    }
}// namespace nema