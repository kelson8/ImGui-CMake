#include "logger.h"
#include <fstream>

// TODO Fix this.

#ifdef LOGGER_ENABLED

// Logger for my ImGui tests.
// This uses spdlog.

// TODO Possibly make this logger use macros later, to toggle them elsewhere
// Such as this: SPDLOG_INFO(text);

//------
// Log functions
//------

/**
 *
 * Initalize the logger with the log prefix and the log file.
 */
Logger::Logger()
{
    filelog = spdlog::basic_logger_mt(Defines::GetLogPrefix(), Defines::GetLogFile());
}

/**
 * Basic function to log to a file, this uses the spdlog library.
 *
 * @param logLevel - The type of log to set, such as LogError::INFO, LogError::WARNING, LogLevel::ERROR.
 * @param textToLog - The text to log to the file.
 */
void Logger::Log(LogLevel logLevel, const std::string &text)
{
    // Set the logger format if needed.
    // filelog->set_pattern("[" + logPrefix + "] %v");

    // This can print out the contents of the log to the screen.
    // spdlog::info(textToLog);

    // Log the text to the file.

    switch (logLevel)
    {
    case LogLevel::LOG_INFO:
        filelog.get()->info(text);
        break;
    case LogLevel::LOG_WARNING:
        filelog.get()->warn(text);
        break;
    case LogLevel::LOG_ERROR:
        filelog.get()->error(text);
        break;
    default:
        break;
    }

    // Flush the logger's buffer after logging
    filelog->flush();

    // filelog->flush_on();
}

#endif // LOGGER_ENABLED