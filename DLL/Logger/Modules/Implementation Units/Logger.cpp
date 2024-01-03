module Logger;

import <chrono>;
import <exception>;
import <format>;
import <fstream>;
import <print>;
import <string>;
import <vector>;

Logger::Logger(const TransportOptionsVect&& transportOptions)
{
    if (transportOptions.size() == 0)
    {
        throw std::exception("Tried to initialise logger without transport options!");
    }

    m_transportOptions = transportOptions;
    m_transportBuffer  = std::vector<std::vector<std::string>>{ transportOptions.size(), {{}} };
}

Logger::~Logger()
{
    Dump(true);
}

void Logger::Error(const String& scope, const Path& path, const String& message)
{
    this->Log(Logger::Level::ERROR, scope, path, message);
}

void Logger::Fatal(const String& scope, const Path& path, const String& message)
{
    this->Log(Logger::Level::FATAL, scope, path, message);
}

void Logger::Info(const String& scope, const Path& path, const String& message)
{
    this->Log(Logger::Level::INFO, scope, path, message);
}

void Logger::Warn(const String& scope, const Path& path, const String& message)
{
    this->Log(Logger::Level::WARN, scope, path, message);
}

void Logger::ForceDump()
{
    Dump(true);
}

const Logger::String Logger::ConvertLogLevelToEmoji(Level level)
{
    if      (level == Level::INFO)  return ":information_source:";
    else if (level == Level::WARN)  return ":warning:";
    else if (level == Level::ERROR) return ":red_circle:";
    else if (level == Level::FATAL) return ":rotating_light:";

    throw std::exception("Invalid level provided in ConvertLogLevelToEmoji function!");
}

const Logger::String Logger::ConvertLogLevelToString(Level level)
{
    if      (level == Level::INFO)  return "INFO";
    else if (level == Level::WARN)  return "WARN";
    else if (level == Level::ERROR) return "ERROR";
    else if (level == Level::FATAL) return "FATAL";

    throw std::exception("Invalid level provided in ConvertLogLevelToString function!");
}

const Logger::String Logger::FormatLog(Format logFormat, Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message) const
{
    using std::chrono::floor;
    using std::chrono::seconds;
    using std::chrono::sys_seconds;
    using std::chrono::system_clock;

    sys_seconds currentTime{ floor<seconds>(system_clock::now())  };
    std::string logMessage = "";
    std::string dateTimeString = std::format("{:%Y-%m-%d %H:%M:%S}", currentTime);

    if (logFormat == Format::TEXT)
    {
        logMessage += std::format
        (
            "[{}] @ [{}]: ({}: ",
            ConvertLogLevelToString(logLevel),
            dateTimeString,
            scope
        );

        if (logPath.size() == 0) logMessage += "none)";
        else
        {
            for (size_t i = 0; i < logPath.size(); i++)
            {
                logMessage += std::format
                (
                    "{}{}{}",
                    logPath.size() == 1 || i == 0 ? "" : " -> ",
                    logPath[i],
                    i == logPath.size() - 1 ? ")" : ""
                );
            }
        }
        logMessage += std::format(" {}", message);
    }
    else if (logFormat == Format::MARKDOWN)
    {
        logMessage += std::format
        (
            "- {} @ [{}]: (`{}`: ",
            ConvertLogLevelToEmoji(logLevel),
            dateTimeString,
            scope
        );

        if (logPath.size() == 0) logMessage += "`none`)";
        else for (size_t i = 0; i < logPath.size(); i++)
        {
            logMessage += std::format
            (
                "{}{}{}",
                logPath.size() == 1 || i == 0 ? "" : " > ",
                std::format(" `{}` ", logPath[i]),
                i == logPath.size() - 1 ? ")" : ""
            );
        }

        logMessage += std::format(" {}", message);
    }

    return logMessage;
}

void Logger::Dump(bool forced)
{
    for (size_t i = 0; i < m_transportBuffer.size(); i++) {
        if (forced || m_transportBuffer[i].size() >= m_transportOptions[i].bufferSize)
        {
            std::ofstream outputFile{ m_transportOptions[i].filePath, std::ios_base::app };

            for (const std::string& line : m_transportBuffer[i])
            {
                std::println(outputFile, "{}", line);
            }
            m_transportBuffer[i].clear();

            outputFile.close();
        }
    }
}

void Logger::Log(Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message)
{
    for (size_t i = 0; i < m_transportOptions.size(); i++)
    {
        int logLevelInt    = (int) logLevel;
        int logLevelMinInt = (int) m_transportOptions[i].minLevel;
        int logLevelMaxInt = (int) m_transportOptions[i].maxLevel;

        if (logLevelInt >= logLevelMinInt && logLevelMaxInt >= logLevelInt) m_transportBuffer[i].push_back(
            FormatLog
            (
                m_transportOptions[i].logFormat,
                logLevel,
                scope,
                logPath,
                message
            )
        );
    }

    Dump(false);
}