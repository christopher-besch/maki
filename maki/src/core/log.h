#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace Lynton {
enum class LogLevel {
    Extra   = spdlog::level::trace,
    General = spdlog::level::debug,
    Warn    = spdlog::level::warn,
    Error   = spdlog::level::err
};

class Log {
private:
    // std::cout and file
    static std::shared_ptr<spdlog::logger> s_lynton_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;
    // std::cerr
    static std::shared_ptr<spdlog::logger> s_error_logger;

public:
    static void init();

    static std::shared_ptr<spdlog::logger>& get_lynton_logger() { return s_lynton_logger; }
    static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }
    static std::shared_ptr<spdlog::logger>& get_error_logger() { return s_error_logger; }

    static void set_lynton_level(LogLevel log_level)
    {
        s_lynton_logger->set_level(static_cast<spdlog::level::level_enum>(log_level));
    }
    static void set_client_level(LogLevel log_level)
    {
        s_client_logger->set_level(static_cast<spdlog::level::level_enum>(log_level));
    }
};

#ifdef NDEBUG
#ifdef __EMSCRIPTEN__
#define raise_critical(...)                                       \
    do {                                                          \
        ::Lynton::Log::get_error_logger()->critical(__VA_ARGS__); \
        emscripten_force_exit(EXIT_FAILURE);                      \
    } while(0)
#else
#define raise_critical(...)                                       \
    do {                                                          \
        ::Lynton::Log::get_error_logger()->critical(__VA_ARGS__); \
        std::exit(EXIT_FAILURE);                                  \
    } while(0)
#endif

#else
#ifdef __EMSCRIPTEN__
#define raise_critical(...)                                                                                       \
    do {                                                                                                          \
        ::Lynton::Log::get_error_logger()->critical(__VA_ARGS__);                                                 \
        ::Lynton::Log::get_error_logger()->critical("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
        emscripten_force_exit(EXIT_FAILURE);                                                                      \
    } while(0)
#else
#define raise_critical(...)                                                                                       \
    do {                                                                                                          \
        ::Lynton::Log::get_error_logger()->critical(__VA_ARGS__);                                                 \
        ::Lynton::Log::get_error_logger()->critical("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
        std::exit(EXIT_FAILURE);                                                                                  \
    } while(0)
#endif
#endif

#define log_lynton_extra(...)   Log::get_lynton_logger()->trace(__VA_ARGS__)
#define log_lynton_general(...) Log::get_lynton_logger()->debug(__VA_ARGS__)
#define log_lynton_warn(...)    Log::get_lynton_logger()->warn(__VA_ARGS__)

#ifdef NDEBUG
#define log_lynton_error(...)                         \
    do {                                              \
        Log::get_lynton_logger()->error(__VA_ARGS__); \
    } while(0)
#else
#define log_lynton_error(...)                                                                         \
    do {                                                                                              \
        Log::get_lynton_logger()->error(__VA_ARGS__);                                                 \
        Log::get_lynton_logger()->error("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
    } while(0)
#endif

#define log_client_extra(...)   ::Lynton::Log::get_client_logger()->trace(__VA_ARGS__)
#define log_client_general(...) ::Lynton::Log::get_client_logger()->debug(__VA_ARGS__)
#define log_client_warn(...)    ::Lynton::Log::get_client_logger()->warn(__VA_ARGS__)

#ifdef NDEBUG
#define log_client_error(...)                                   \
    do {                                                        \
        ::Lynton::Log::get_client_logger()->error(__VA_ARGS__); \
    } while(0)
#else
#define log_client_error(...)                                                                                   \
    do {                                                                                                        \
        ::Lynton::Log::get_client_logger()->error(__VA_ARGS__);                                                 \
        ::Lynton::Log::get_client_logger()->error("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
    } while(0)
#endif
} // namespace Lynton
