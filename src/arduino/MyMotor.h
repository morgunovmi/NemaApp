#pragma once

#include "utils/MySerial.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

enum eSyringeType
{
    ONE_ML,
    TWO_ML,
    FIVE_ML
};

class MyMotor
{
public:
    MyMotor(const std::string& com_port, DWORD COM_BAUD_RATE)
        : m_serial(com_port, COM_BAUD_RATE),
          m_currentSyringe(FIVE_ML), m_volToStepCoefs{4285, 4285, 4285}
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

                j.at("mlToStep1").get_to(m_volToStepCoefs[0]);
                j.at("mlToStep2").get_to(m_volToStepCoefs[1]);
                j.at("mlToStep5").get_to(m_volToStepCoefs[2]);
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
        else
        {
            spdlog::error("Couldn't connect to {}", com_port);
        }
    }

    [[nodiscard]] bool IsConnected() const { return m_serial.IsConnected(); }

    void Go(double dist, double speed)
    {
        nlohmann::json j;
        j["command"] = "Go";
        j["amount"] = dist * m_volToStepCoefs[m_currentSyringe];
        j["speed"] = speed * m_volToStepCoefs[m_currentSyringe] / 60.0;

        if (m_serial.WriteSerialPort(j.dump()))
        {
            spdlog::info("Sent \"{}\"", j.dump());
            spdlog::info("Received \"{}\"", m_serial.ReadSerialPort());
        }
        else
        {
            spdlog::error("Couldn't send string");
        }
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
        else
        {
            spdlog::error("Couldn't send string");
        }
    }

    std::string GetSetupPath() const { return SETUP_PATH; }

    std::array<float, 3> m_volToStepCoefs{};
    eSyringeType m_currentSyringe;

private:
    MySerial m_serial;

    const std::string SETUP_PATH = "setup.json";
};
