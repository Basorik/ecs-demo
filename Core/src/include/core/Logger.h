#pragma once
#include <iostream>
#include <format>


namespace Core {
    /*template <typename T>
    void GameLog(const char* varName, T var) {
        std::cout << std::format("{}: {}\n", varName, var);
    }*/
    /**
     * @class Logger
     * @brief A simple static logger class for console output.
     */
    class Logger {
    public:
        /**
         * @enum Level
         * @brief Defines the severity level of a log message.
         */
        enum class Level {
            Info,
            Warning,
            Error
        };

        /**
         * @brief Logs a message to the console.
         * @param level The severity level of the message.
         * @param message The message to log.
         */
        static void log(Level level, const std::string& message);
    };
}