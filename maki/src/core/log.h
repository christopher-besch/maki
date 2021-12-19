#pragma once

#include "pch.h"

// TODO: move to pch.h, produces weird error when attempting -> break stb compilation in stb.cpp
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Maki {

enum class LogLevel {
    Extra   = spdlog::level::trace,
    General = spdlog::level::debug,
    Warn    = spdlog::level::warn,
    Error   = spdlog::level::err
};

class Log {
private:
    // stdout and file
    static std::shared_ptr<spdlog::logger> s_maki_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;

    // stderr
    static std::shared_ptr<spdlog::logger> s_error_logger;

public:
    static void init();

    static std::shared_ptr<spdlog::logger>& get_maki_logger() { return s_maki_logger; }
    static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }
    static std::shared_ptr<spdlog::logger>& get_error_logger() { return s_error_logger; }

    static void set_maki_level(LogLevel log_level)
    {
        s_maki_logger->set_level(static_cast<spdlog::level::level_enum>(log_level));
    }
    static void set_client_level(LogLevel log_level)
    {
        s_client_logger->set_level(static_cast<spdlog::level::level_enum>(log_level));
    }
};

// asserts
#ifdef NDEBUG
#define MAKI_RAISE_CRITICAL(...)                                \
    do {                                                        \
        ::Maki::Log::get_error_logger()->critical(__VA_ARGS__); \
        std::exit(EXIT_FAILURE);                                \
    } while(0)

#define MAKI_ASSERT(x, ...)

#else
#define MAKI_RAISE_CRITICAL(...)                                                                                \
    do {                                                                                                        \
        ::Maki::Log::get_error_logger()->critical(__VA_ARGS__);                                                 \
        ::Maki::Log::get_error_logger()->critical("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
        std::exit(EXIT_FAILURE);                                                                                \
    } while(0)

#define MAKI_ASSERT(x, ...)                  \
    do {                                     \
        if(!x)                               \
            MAKI_RAISE_CRITICAL(__VA_ARGS__) \
    } while(0)
#endif

// Maki logger -> to be used by Maki internally
#define MAKI_LOG_EXTRA(...)   Log::get_maki_logger()->trace(__VA_ARGS__)
#define MAKI_LOG_GENERAl(...) Log::get_maki_logger()->debug(__VA_ARGS__)
#define MAKI_LOG_WARN(...)    Log::get_maki_logger()->warn(__VA_ARGS__)

#ifdef NDEBUG
#define MAKI_LOG_ERROR(...)                         \
    do {                                            \
        Log::get_maki_logger()->error(__VA_ARGS__); \
    } while(0)
#else
#define MAKI_LOG_ERROR(...)                                                                         \
    do {                                                                                            \
        Log::get_maki_logger()->error(__VA_ARGS__);                                                 \
        Log::get_maki_logger()->error("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
    } while(0)
#endif

// client logger -> can be used by the client
#define MAKI_CLIENT_LOG_EXTRA(...)   ::Maki::Log::get_client_logger()->trace(__VA_ARGS__)
#define MAKI_CLIENT_LOG_GENERAL(...) ::Maki::Log::get_client_logger()->debug(__VA_ARGS__)
#define MAKI_CLIENT_LOG_WARN(...)    ::Maki::Log::get_client_logger()->warn(__VA_ARGS__)

#ifdef NDEBUG
#define MAKI_CLIENT_LOG_ERROR(...)                            \
    do {                                                      \
        ::Maki::Log::get_client_logger()->error(__VA_ARGS__); \
    } while(0)
#else
#define MAKI_CLIENT_LOG_ERROR(...)                                                                            \
    do {                                                                                                      \
        ::Maki::Log::get_client_logger()->error(__VA_ARGS__);                                                 \
        ::Maki::Log::get_client_logger()->error("(in {}:{}; in function: {})", __FILE__, __LINE__, __func__); \
    } while(0)
#endif

} // namespace Maki
