#include "core/Logger.h"

namespace Core {

    // Implementation of the static log function
    void Logger::log(Level level, const std::string& message) {
        // Prepend the log level to the message and output to the appropriate stream
        switch (level) {
        case Level::Info:
            std::cout << "[INFO] " << message << std::endl;
            break;
        case Level::Warning:
            // Warnings and Errors go to the standard error stream
            std::cerr << "[WARNING] " << message << std::endl;
            break;
        case Level::Error:
            std::cerr << "[ERROR] " << message << std::endl;
            break;
        }
    }

} // namespace core
