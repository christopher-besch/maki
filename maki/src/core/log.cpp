#include "pch.h"

#include "log.h"

namespace Maki {

void Log::init()
{
    try {
        // log to console and file
        std::vector<spdlog::sink_ptr> default_log_sinks;
        default_log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        default_log_sinks[0]->set_pattern("%^[%T] %n: %v%$");
        // log to std error stream
        std::vector<spdlog::sink_ptr> error_log_sinks;
        error_log_sinks.emplace_back(std::make_shared<spdlog::sinks::stderr_color_sink_mt>());
        error_log_sinks[0]->set_pattern("%^[%T] %n: %v%$");

        s_maki_logger   = std::make_shared<spdlog::logger>("Maki", default_log_sinks.begin(), default_log_sinks.end());
        s_client_logger = std::make_shared<spdlog::logger>("Client", default_log_sinks.begin(), default_log_sinks.end());
        s_error_logger  = std::make_shared<spdlog::logger>("Error", error_log_sinks.begin(), error_log_sinks.end());

        spdlog::register_logger(s_maki_logger);
        s_maki_logger->set_level(spdlog::level::trace);
        s_maki_logger->flush_on(spdlog::level::trace);

        spdlog::register_logger(s_client_logger);
        s_client_logger->set_level(spdlog::level::trace);
        s_client_logger->flush_on(spdlog::level::trace);

        spdlog::register_logger(s_error_logger);
        s_error_logger->set_level(spdlog::level::critical);
        s_error_logger->flush_on(spdlog::level::critical);
    }
    catch(const spdlog::spdlog_ex& ex) {
        std::cerr << "Log init failed: " << ex.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

}; // namespace Maki
