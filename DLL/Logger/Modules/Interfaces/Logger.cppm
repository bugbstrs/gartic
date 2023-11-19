export module Logger;
import LogLevel;
import LogFormat;
import TransportOptions;
import <vector>;
import <string>;

export class Logger
{
public:
	using TransportOptions = TransportOptions;
	using Format = LogFormat;
	using Level = LogLevel;

	Logger(const std::vector<TransportOptions>& transportOptions);

	void Info(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	void Warn(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	void Error(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	void Fatal(const std::string& scope, const std::vector<std::string>& path, const std::string& message);

	void ForceDump();

	~Logger();

	static const std::string ConvertLogLevelToString(Level level);
	static const std::string ConvertLogLevelToEmoji(Level level);
private:
	std::vector<std::vector<std::string>> m_transportBuffer;
	std::vector<TransportOptions> m_transportOptions;
	const std::string FormatLog(Format logFormat, Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message) const;
	void Log(Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message);
	void Dump(bool forced = false);
};