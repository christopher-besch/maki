#include "log.h"

#include "pch.h"

namespace Lynton {
std::shared_ptr<spdlog::logger> Log::s_lynton_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;
std::shared_ptr<spdlog::logger> Log::s_error_logger;

void Log::init()
{
    try {
        // log to console and file
        std::vector<spdlog::sink_ptr> default_log_sinks;
        default_log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#ifndef __EMSCRIPTEN__
        default_log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("lynton.log", true));
#endif
        // log to std error stream
        std::vector<spdlog::sink_ptr> error_log_sinks;
        error_log_sinks.emplace_back(std::make_shared<spdlog::sinks::stderr_color_sink_mt>());
        default_log_sinks[0]->set_pattern("%^[%T] %n: %v%$");
#ifndef __EMSCRIPTEN__
        default_log_sinks[1]->set_pattern("[%T] [%l] %n: %v");
#endif
        error_log_sinks[0]->set_pattern("%^[%T] %n: %v%$");

        s_lynton_logger = std::make_shared<spdlog::logger>("Lynton", begin(default_log_sinks), end(default_log_sinks));
        s_client_logger = std::make_shared<spdlog::logger>("Client", begin(default_log_sinks), end(default_log_sinks));
        s_error_logger  = std::make_shared<spdlog::logger>("Error", begin(error_log_sinks), end(error_log_sinks));

        spdlog::register_logger(s_lynton_logger);
        s_lynton_logger->set_level(spdlog::level::trace);
        s_lynton_logger->flush_on(spdlog::level::trace);

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
} // namespace Lynton
