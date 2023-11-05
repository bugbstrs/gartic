module Logger;
import <exception>;
import <vector>;
import <fstream>;
import <string>;
import <format>;
import <chrono>;

Logger::Logger(const std::vector<TransportOptions>& transportOptions)
{
	if (transportOptions.size() == 0)
	{
		throw std::exception("Tried to initialise logger without transport options!");
	}

	m_transportOptions = transportOptions;
	m_transportBuffer = std::vector<std::vector<std::string>>{ transportOptions.size(), {{}} };
}

const std::string Logger::FormatLog(Format logFormat, Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message) const
{
	std::string logMessage = "";
	//const auto now = std::chrono::system_clock::now();
	//const std::time_t time = std::chrono::system_clock::to_time_t(now);
	// TODO: get time
	std::string dateTimeString = ".";

	if (logFormat == Format::TEXT)
	{
		logMessage += std::format(
			"[{}] on [{}]: ({}: ",
			ConvertLogLevelToString(logLevel),
			dateTimeString,
			scope
		);

		if (logPath.size() == 0) logMessage += "none)";
		else
		{
			for (int i = 0; i < logPath.size(); i++)
			{
				logMessage += std::format(
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
		logMessage += std::format(
			"- {} @ [{}]: (`{}`: ",
			ConvertLogLevelToEmoji(logLevel),
			dateTimeString,
			scope
		);

		if (logPath.size() == 0) logMessage += "`none`)";
		else for (int i = 0; i < logPath.size(); i++)
		{
			logMessage += std::format(
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

void Logger::Log(Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message)
{
	for (int i = 0; i < m_transportOptions.size(); i++)
	{
		int logLevelInt = (int)logLevel;
		int logLevelMinInt = (int)m_transportOptions[i].minLevel;
		int logLevelMaxInt = (int)m_transportOptions[i].maxLevel;

		if (logLevelInt >= logLevelMinInt && logLevelMaxInt >= logLevelInt) m_transportBuffer[i].push_back(
			FormatLog(
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

void Logger::Dump(bool forced)
{
	for (int i = 0; i < m_transportBuffer.size(); i++) {
		if (forced || m_transportBuffer[i].size() >= m_transportOptions[i].bufferSize)
		{
			std::ofstream outputFile{ m_transportOptions[i].filePath, std::ios_base::app };

			for (const std::string& line : m_transportBuffer[i])
			{
				outputFile << line << '\n';
			}
			m_transportBuffer[i].clear();

			outputFile.close();
		}
	}
}

void Logger::Info(const std::string& scope, const std::vector<std::string>& path, const std::string& message)
{
	this->Log(Logger::Level::INFO, scope, path, message);
}

void Logger::Warn(const std::string& scope, const std::vector<std::string>& path, const std::string& message)
{
	this->Log(Logger::Level::WARN, scope, path, message);
}

void Logger::Error(const std::string& scope, const std::vector<std::string>& path, const std::string& message)
{
	this->Log(Logger::Level::ERROR, scope, path, message);
}

void Logger::Fatal(const std::string& scope, const std::vector<std::string>& path, const std::string& message)
{
	this->Log(Logger::Level::FATAL, scope, path, message);
}

void Logger::ForceDump()
{
	Dump(true);
}

Logger::~Logger()
{
	Dump(true);
}

const std::string Logger::ConvertLogLevelToString(Level level)
{
	if (level == Level::INFO) return "INFO";
	else if (level == Level::WARN) return "WARN";
	else if (level == Level::ERROR) return "ERROR";
	else if (level == Level::FATAL) return "FATAL";

	throw std::exception("Invalid level provided in ConvertLogLevelToString function!");
}

const std::string Logger::ConvertLogLevelToEmoji(Level level)
{
	if (level == Level::INFO) return "ℹ️";
	else if (level == Level::WARN) return "⚠️";
	else if (level == Level::ERROR) return "🔴";
	else if (level == Level::FATAL) return "🚨";

	throw std::exception("Invalid level provided in ConvertLogLevelToEmoji function!");
}
