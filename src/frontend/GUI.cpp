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
        m_hubballiFont = io.Fonts->AddFontFromFileTTF(
                "./resources/fonts/Montserrat-Light.ttf", 20);
        ImGui::SFML::UpdateFontTexture();

        auto& style = ImGui::GetStyle();
        style.WindowPadding = {10.f, 10.f};
        style.FrameRounding = 6.0f;
        style.GrabRounding = 12.0f;
        style.FramePadding = ImVec2(12, 5);
        style.ItemSpacing = ImVec2(10, 6);
        style.ItemInnerSpacing = ImVec2(6, 4);
        style.ScrollbarSize = 20.f;
        style.GrabMinSize = 18.f;

        style.WindowRounding = 12.f;
        style.ScrollbarRounding = 0.f;

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

        m_keyStates[sf::Keyboard::Left] = {false, false};
        m_keyStates[sf::Keyboard::Right] = {false, false};
        m_keyStates[sf::Keyboard::Space] = {false, false};
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
                        case sf::Keyboard::Left:
                            if (!m_keyStates[sf::Keyboard::Left].isPressed)
                            {
                                m_keyStates[sf::Keyboard::Left].isPressed =
                                        true;
                                m_keyStates[sf::Keyboard::Left].stateChanged =
                                        true;
                            }
                            break;
                        case sf::Keyboard::Right:
                            if (!m_keyStates[sf::Keyboard::Right].isPressed)
                            {
                                m_keyStates[sf::Keyboard::Right].isPressed =
                                        true;
                                m_keyStates[sf::Keyboard::Right].stateChanged =
                                        true;
                            }
                            break;
                        case sf::Keyboard::Space:
                            if (!m_keyStates[sf::Keyboard::Space].isPressed)
                            {
                                m_keyStates[sf::Keyboard::Space].isPressed =
                                        true;
                                m_keyStates[sf::Keyboard::Space].stateChanged =
                                        true;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Left:
                            if (m_keyStates[sf::Keyboard::Left].isPressed)
                            {
                                m_keyStates[sf::Keyboard::Left].isPressed =
                                        false;
                                m_keyStates[sf::Keyboard::Left].stateChanged =
                                        true;
                            }
                            break;
                        case sf::Keyboard::Right:
                            if (m_keyStates[sf::Keyboard::Right].isPressed)
                            {
                                m_keyStates[sf::Keyboard::Right].isPressed =
                                        false;
                                m_keyStates[sf::Keyboard::Right].stateChanged =
                                        true;
                            }
                            break;
                        case sf::Keyboard::Space:
                            if (m_keyStates[sf::Keyboard::Space].isPressed)
                            {
                                m_keyStates[sf::Keyboard::Space].isPressed =
                                        false;
                                m_keyStates[sf::Keyboard::Space].stateChanged =
                                        true;
                            }
                            break;
                    }
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
                if (ImGui::MenuItem("App Log", nullptr, &m_bShowAppLog)) {}
                if (ImGui::MenuItem("Dumper Controls", nullptr, &m_bShowDumper))
                {
                }
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
        if (m_bShowMotors) ShowMotorControls();
        if (m_bShowDumper) ShowDumperControls();

#ifndef NDEBUG
        ImGui::ShowDemoWindow();
#endif

        ImGui::PopFont();
        ImGui::SFML::Render(m_window);
    }

    void GUI::Shutdown() { ImGui::SFML::Shutdown(); }

    void GUI::HandleInputCommands(MyMotor& m1, MyMotor& m2, uint32_t selected,
                                  float speed1, float speed2)
    {
        for (auto& [key, state]: m_keyStates)
        {
            if (state.stateChanged)
            {
                MyMotor& selectedMotor = selected == 0 ? m1 : m2;
                float selectedSpeed = selected == 0 ? speed1 : speed2;
                switch (key)
                {
                    case sf::Keyboard::Left:
                    {
                        if (state.isPressed)
                        {
                            selectedMotor.Go(20, selectedSpeed);
                        }
                        else { selectedMotor.Stop(); }
                    }
                    break;
                    case sf::Keyboard::Right:
                    {
                        if (state.isPressed)
                        {
                            selectedMotor.Go(-20, selectedSpeed);
                        }
                        else { selectedMotor.Stop(); }
                    }
                    break;
                    case sf::Keyboard::Space:
                    {
                        if (state.isPressed)
                        {
                            m1.Stop();
                            m2.Stop();
                        }
                    }
                    break;
                }
                m_keyStates[key].stateChanged = false;
            }
        }
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

            const int numPorts = static_cast<int>(portStrs.size());
            static MyMotor motor1{"motor1"}, motor2{"motor2"};

            if (numPorts > 1 && !(motor1.IsConnected() && motor2.IsConnected()))
            {
                motor1.Connect(fmt::format("\\\\.\\{}", portStrs[numPorts - 2]),
                               CBR_9600);
                motor2.Connect(fmt::format("\\\\.\\{}", portStrs[numPorts - 1]),
                               CBR_9600);
            }

            if (!(motor1.IsConnected() && motor2.IsConnected()))
            {
                ImGui::Text("Please connect both motors\n");
                ImGui::BeginDisabled();
            }

            ImGui::PushItemWidth(m_inputFieldWidth);

            if (motor1.IsConnected() && motor2.IsConnected())
            {
                static auto currentPort1 = numPorts - 2;
                static auto currentPort2 = numPorts - 1;

                ImGui::BeginGroup();
                Combo("Motor 1 Port", &currentPort1, portStrs,
                      static_cast<int>(portStrs.size()));
                if (ImGui::Button("Connect 1", ImVec2(m_inputFieldWidth, 30.f)))
                {
                    motor1.Connect(
                            fmt::format("\\\\.\\{}", portStrs[currentPort1]),
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
                ImGui::EndGroup();
                ImGui::SameLine();

                ImGui::BeginGroup();
                Combo("Motor 2 Port", &currentPort2, portStrs,
                      static_cast<int>(portStrs.size()));
                if (ImGui::Button("Connect 2", ImVec2(m_inputFieldWidth, 30.f)))
                {
                    motor2.Connect(
                            fmt::format("\\\\.\\{}", portStrs[currentPort2]),
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
                ImGui::EndGroup();
            }

            ImGui::Dummy({0.f, 10.f});
            ImGui::Text("Equipment setup");
            ImGui::Separator();

            static std::vector<std::string> syringes{"1 ml", "2 ml", "5 ml"};
            static std::vector<std::string> modes{"FULL", "1/2",  "1/4",
                                                  "1/8",  "1/16", "1/32"};

            ImGui::BeginGroup();
            Combo("Syringe 1", (int*) &motor1.m_currentSyringe, syringes,
                  static_cast<int>(syringes.size()));
            Combo("Driver mode 1", (int*) &motor1.m_currentDriverMode, modes,
                  static_cast<int>(modes.size()));
            ImGui::EndGroup();
            ImGui::SameLine();

            ImGui::BeginGroup();
            Combo("Syringe 2", (int*) &motor2.m_currentSyringe, syringes,
                  static_cast<int>(syringes.size()));
            Combo("Driver mode 2", (int*) &motor2.m_currentDriverMode, modes,
                  static_cast<int>(modes.size()));
            ImGui::EndGroup();

            ImGui::Dummy({0.f, 10.f});
            ImGui::Text("Motion parameters");
            ImGui::Separator();

            ImGui::BeginGroup();
            ImGui::DragFloat("vol to step coef 1",
                             &motor1.m_volToStepCoefs[motor1.m_currentSyringe],
                             0.5, 2000, 15000);
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                if (auto ofs = std::ofstream{motor1.GetSetupPath()})
                {
                    motorState[motor1.Name()]["mlToStep1"] =
                            motor1.m_volToStepCoefs[0];
                    motorState[motor1.Name()]["mlToStep2"] =
                            motor1.m_volToStepCoefs[1];
                    motorState[motor1.Name()]["mlToStep5"] =
                            motor1.m_volToStepCoefs[2];

                    ofs << motorState.dump(4);
                }
            }
            static float speed1 = 23.0;
            ImGui::DragFloat("Speed 1", &speed1, 0.5, 0, 30);
            static float amount1 = 1;
            ImGui::DragFloat("Amount 1", &amount1, 0.5, 0, 30);
            ImGui::EndGroup();
            ImGui::SameLine();

            ImGui::BeginGroup();
            ImGui::DragFloat("vol to step coef 2",
                             &motor2.m_volToStepCoefs[motor2.m_currentSyringe],
                             0.5, 2000, 15000);
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                if (auto ofs = std::ofstream{motor2.GetSetupPath()})
                {
                    motorState[motor2.Name()]["mlToStep1"] =
                            motor2.m_volToStepCoefs[0];
                    motorState[motor2.Name()]["mlToStep2"] =
                            motor2.m_volToStepCoefs[1];
                    motorState[motor2.Name()]["mlToStep5"] =
                            motor2.m_volToStepCoefs[2];

                    ofs << motorState.dump(4);
                }
            }
            ImGui::SameLine();
            HelpMarker("These coefficients are used to convert from "
                       "milliliters to motor steps\n"
                       "All amounts below are in milliliters");
            static float speed2 = 23.0;
            ImGui::DragFloat("Speed 2", &speed2, 0.5, 0, 30);
            ImGui::SameLine();
            HelpMarker("milliliters per minute");

            static float amount2 = 1;
            ImGui::DragFloat("Amount 2", &amount2, 0.5, 0, 30);
            ImGui::SameLine();
            HelpMarker("milliliters");
            ImGui::EndGroup();

            ImGui::Dummy({0.f, 10.f});
            ImGui::Text("Motion control");
            ImGui::Separator();

            ImGui::BeginGroup();
            if (ImGui::Button("Forward 1", ImVec2(150.f, 40.f)))
            {
                motor1.Go(amount1, speed1);
            }
            if (ImGui::Button("Back 1", ImVec2(150.f, 40.f)))
            {
                motor1.Go(-amount1, speed1);
            }
            if (ImGui::Button("Forward Both", ImVec2(150.f, 40.f)))
            {
                motor1.Go(amount1, speed1);
                motor2.Go(amount2, speed2);
            }
            ImGui::EndGroup();
            ImGui::SameLine();

            ImGui::BeginGroup();
            if (ImGui::Button("Forward 2", ImVec2(150.f, 40.f)))
            {
                motor2.Go(amount2, speed2);
            }
            if (ImGui::Button("Back 2", ImVec2(150.f, 40.f)))
            {
                motor2.Go(-amount2, speed2);
            }
            if (ImGui::Button("Back Both", ImVec2(150.f, 40.f)))
            {
                motor1.Go(-amount1, speed1);
                motor2.Go(-amount2, speed2);
            }
            ImGui::EndGroup();

            if (ImGui::Button("Stop both", ImVec2(150.f, 60.f)))
            {
                motor1.Stop();
                motor2.Stop();
            }

            ImGui::Dummy({0.f, 10.f});
            ImGui::Text("Keyboard control");
            ImGui::Separator();

            static int selected = 0;
            std::vector<std::string> motors{"Motor 1", "Motor 2"};
            Combo("Keyboard controlled motor", &selected, motors,
                  static_cast<int>(motors.size()));
            ImGui::TextColored(
                    {0.0, 0.8, 0.0, 1.0},
                    "Use <- and -> buttons for fine control of selected motor");
            ImGui::TextColored({0.0, 0.8, 0.0, 1.0},
                               "Use Spacebar to stop both motors");


            HandleInputCommands(motor1, motor2, selected, speed1, speed2);

            if (!(motor1.IsConnected() && motor2.IsConnected()))
            {
                ImGui::EndDisabled();
            }

            ImGui::PopItemWidth();
        }
        ImGui::End();
    }

    void GUI::ShowDumperControls()
    {
        if (ImGui::Begin("Dumper Controls", &m_bShowDumper))
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

            const int numPorts = static_cast<int>(portStrs.size());
            static MyMotor dumper{"dumper"};
            static auto currentPort = numPorts - 1;

            ImGui::PushItemWidth(m_inputFieldWidth);
            if (numPorts > 0)
            {
                Combo("Motor port", &currentPort, portStrs,
                      static_cast<int>(portStrs.size()));

                if (ImGui::Button("Connect", ImVec2(m_inputFieldWidth, 30.f)))
                {
                    dumper.Connect(
                            fmt::format("\\\\.\\{}", portStrs[currentPort]),
                            CBR_9600);
                }
            }

            if (!dumper.IsConnected())
            {
                ImGui::Text("Please connect the motor\n");
                ImGui::BeginDisabled();
            }

            static std::vector<std::string> syringes{"1 ml", "2 ml", "5 ml"};
            static std::vector<float> syringeVolumes{1.0f, 2.0f, 5.0f};
            static std::vector<std::string> modes{"FULL", "1/2",  "1/4",
                                                  "1/8",  "1/16", "1/32"};

            ImGui::BeginGroup();
            Combo("Syringe", (int*) &dumper.m_currentSyringe, syringes,
                  static_cast<int>(syringes.size()));
            Combo("Driver mode", (int*) &dumper.m_currentDriverMode, modes,
                  static_cast<int>(modes.size()));
            ImGui::EndGroup();

            ImGui::Dummy(ImVec2(0.f, 20.f));

            ImGui::BeginGroup();
            ImGui::DragFloat("vol to step coef",
                             &dumper.m_volToStepCoefs[dumper.m_currentSyringe],
                             0.5, 2000, 15000);
            ImGui::SameLine();
            HelpMarker("These coefficients are used to convert from "
                       "milliliters to motor steps\n");
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                if (auto ofs = std::ofstream{dumper.GetSetupPath()})
                {
                    motorState[dumper.Name()]["mlToStep1"] =
                            dumper.m_volToStepCoefs[0];
                    motorState[dumper.Name()]["mlToStep2"] =
                            dumper.m_volToStepCoefs[1];
                    motorState[dumper.Name()]["mlToStep5"] =
                            dumper.m_volToStepCoefs[2];

                    ofs << motorState.dump(4);
                }
            }
            static float speed = 23.0;
            ImGui::DragFloat("Speed", &speed, 0.5, 0, 30);
            ImGui::SameLine();
            HelpMarker("milliliters per minute");
            static int amount = 5;
            ImGui::DragInt("Amount in percent", &amount, 1, 0, 100);
            ImGui::EndGroup();

            ImGui::Dummy(ImVec2(0.f, 20.f));

            if (ImGui::Button("Dump", ImVec2(150.f, 40.f)))
            {
                dumper.Go(amount / 100.f *
                                  syringeVolumes[dumper.m_currentSyringe],
                          speed);
            }

            ImGui::PopItemWidth();

            if (!dumper.IsConnected()) { ImGui::EndDisabled(); }
        }
        ImGui::End();
    }
}// namespace nema