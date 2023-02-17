#pragma once

#include "utils/MySerial.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

enum eSyringeType
{
    ONE_ML,
    TWO_ML,
    FIVE_ML,
    TEN_ML,
    FTEEN_ML,
    TWENTY_ML,
    TWFIVE_ML,
    FIFTY_ML,
    SYRINGE_MAX
};

enum eDriverMode
{
    FULL,
    HALF,
    QUARTER,
    EIGHTH,
    ONE_OVER_16,
    ONE_OVER_32
};

static const std::array<double, 6> multipliers{1.0, 2.0, 4.0, 8.0, 16.0, 32.0};

class MyMotor
{
public:
    MyMotor(const std::string& name)
        : m_name(name), m_currentSyringe(FIVE_ML),
          m_currentDriverMode(ONE_OVER_32), m_volToStepCoefs{4285, 4285, 4285,
                                                             4285, 4285, 4285,
                                                             4285, 4285}
    {
        // spdlog::info("Before loading");
        LoadCoeffs();
        // spdlog::info("after loading");
    }

    MyMotor(const std::string& name, const std::string& com_port,
            DWORD COM_BAUD_RATE)
        : m_serial(com_port, COM_BAUD_RATE), m_currentSyringe(FIVE_ML),
          m_name(name),
          m_currentDriverMode(ONE_OVER_32), m_volToStepCoefs{4285, 4285, 4285,
                                                             4285, 4285, 4285,
                                                             4285, 4285}
    {
        LoadCoeffs();
    }

    void LoadCoeffs()
    {
        if (std::filesystem::exists(std::filesystem::path{SETUP_PATH}))
        {
            if (auto ifs = std::ifstream{SETUP_PATH})
            {
                const auto j = nlohmann::json::parse(ifs);

                if (j.contains(m_name))
                {
                    j.at(m_name).at("mlToStep1").get_to(m_volToStepCoefs[0]);
                    j.at(m_name).at("mlToStep2").get_to(m_volToStepCoefs[1]);
                    j.at(m_name).at("mlToStep5").get_to(m_volToStepCoefs[2]);
                    j.at(m_name).at("mlToStep10").get_to(m_volToStepCoefs[3]);
                    j.at(m_name).at("mlToStep15").get_to(m_volToStepCoefs[4]);
                    j.at(m_name).at("mlToStep20").get_to(m_volToStepCoefs[5]);
                    j.at(m_name).at("mlToStep25").get_to(m_volToStepCoefs[6]);
                    j.at(m_name).at("mlToStep50").get_to(m_volToStepCoefs[7]);
                }
            }
        }
    }

    void Connect(const std::string& com_port, DWORD COM_BAUD_RATE)
    {
        m_serial.Connect(com_port, COM_BAUD_RATE);

        if (m_serial.IsConnected())
        {
            spdlog::info("Connected to {} successfully", com_port);
        }
        else { spdlog::error("Couldn't connect to {}", com_port); }
    }

    void Update()
    {
        if (!m_serial.WriteSerialPort("meme")) { m_serial.CloseSerialPort(); }
    }

    const std::string& Name() const { return m_name; }

    [[nodiscard]] bool IsConnected() const { return m_serial.IsConnected(); }

    void Go(double dist, double speed)
    {
        nlohmann::json j;
        j["command"] = "Go";
        j["amount"] = dist * m_volToStepCoefs[m_currentSyringe] *
                      multipliers[m_currentDriverMode];
        j["speed"] = speed * m_volToStepCoefs[m_currentSyringe] *
                     multipliers[m_currentDriverMode] / 60.0;

        if (m_serial.WriteSerialPort(j.dump()))
        {
            spdlog::info("Sent \"{}\"", j.dump());
            spdlog::info("Received \"{}\"", m_serial.ReadSerialPort());
        }
        else { spdlog::error("Couldn't send string"); }
    }

    void Stop()
    {
        nlohmann::json j;
        j["command"] = "Stop";

        if (m_serial.WriteSerialPort(j.dump()))
        {
            spdlog::info("Sent \"{}\"", j.dump());
            spdlog::info("Received \"{}\"", m_serial.ReadSerialPort());
        }
        else { spdlog::error("Couldn't send string"); }
    }

    std::string GetSetupPath() const { return SETUP_PATH; }

    std::array<float, 8> m_volToStepCoefs{};
    eSyringeType m_currentSyringe;
    eDriverMode m_currentDriverMode;

private:
    MySerial m_serial;
    const std::string m_name;

    const std::string SETUP_PATH = "setup.json";
};