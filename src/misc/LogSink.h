#include <spdlog/sinks/base_sink.h>
#include <mutex>

#include "misc/Log.h"

/**
 * Class that defines a special spdlog sink that dumps output to a Log instance
 *
 * @tparam Mutex mutex type for spdlog
 */
template<typename Mutex>
class LogSink : public spdlog::sinks::base_sink<Mutex>
{
public:
    explicit LogSink(nema::Log& log)
        : spdlog::sinks::base_sink<Mutex>(), m_log(log)
    {
    }

private:
    nema::Log& m_log;

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        // log_msg is a struct containing the log entry info like level, timestamp, thread id etc.
        // msg.raw contains pre formatted log

        // If needed (very likely but not mandatory), the sink formats the message before sending it to its final destination:
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        m_log.AddLog(fmt::to_string(formatted).c_str());
    }

    void flush_() override {}
};

using LogSinkMt = LogSink<std::mutex>;