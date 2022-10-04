#pragma once

#include "utils/MySerial.h"
#include <nlohmann/json.hpp>

class MyMotor
{
public:
    MyMotor(const std::string& com_port, DWORD COM_BAUD_RATE)
        : m_serial(com_port, COM_BAUD_RATE), m_volToStepCoef(4285.0)
    {
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
        j["amount"] = dist * m_volToStepCoef;
        j["speed"] = speed * m_volToStepCoef / 60.0;

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
    float m_volToStepCoef;

private:
    MySerial m_serial;
};
