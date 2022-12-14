#include <fmt/format.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <vector>

#include "frontend/App.h"
#include "misc/Log.h"
#include "misc/LogSink.h"

int main()
{
    try
    {
        nema::Log log;

        auto sink = std::make_shared<LogSinkMt>(log);

        auto console_sink =
                std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                "logs/app_log.txt");

        std::vector<spdlog::sink_ptr> sinks{sink, console_sink, file_sink};
        auto MyLogger = std::make_shared<spdlog::logger>(
                "MyLogger", sinks.begin(), sinks.end());
        //        MyLogger->set_pattern(">> [%T] {%t} (%^%l%$) %v <<");
        MyLogger->set_pattern(">> (%^%l%$) %v <<");

#ifndef NDEBUG
        MyLogger->set_level(spdlog::level::trace);
#else
        MyLogger->set_level(spdlog::level::info);
#endif
        spdlog::set_default_logger(MyLogger);
        spdlog::debug("Logger setup in main");

        const auto width = 1400;
        const auto height = 800;
        const auto antialiasingLevel = 8;

        sf::ContextSettings settings{};
        settings.antialiasingLevel = antialiasingLevel;

        spdlog::info("\n>> NEW LAUNCH <<\n");
        nema::App app{width, height, settings, log};
        app.Run();
    }
    catch (std::exception& e)
    {
        fmt::print("Error {}", e.what());
    }

    return EXIT_SUCCESS;
}