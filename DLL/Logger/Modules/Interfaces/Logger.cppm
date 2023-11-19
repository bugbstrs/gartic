export module Logger;
import LogLevel;
import LogFormat;
import TransportOptions;
import <vector>;
import <string>;

export class __declspec(dllexport) Logger
{
public:
	#pragma region Logger
	using TransportOptions = TransportOptions;
	using Format = LogFormat;
	using Level = LogLevel;
	#pragma endregion using statements for TransportOptions, LogFormat & LogLevel

	#pragma region Logger
	Logger(const std::vector<TransportOptions>& transportOptions);
	~Logger();
	#pragma endregion constructors and destructor

	#pragma region Logger
	void Info(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	void Warn(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	void Error(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	void Fatal(const std::string& scope, const std::vector<std::string>& path, const std::string& message);
	#pragma endregion logging functions for the 4 levels: info/warn/error/fatal
	
	#pragma region Logger
	void ForceDump();
	#pragma endregion other functions

	#pragma region Logger
	static const std::string ConvertLogLevelToString(Level level);
	static const std::string ConvertLogLevelToEmoji(Level level);
	#pragma endregion static members (converting log levels to emoji/string)
private:
	#pragma region Logger
	std::vector<std::vector<std::string>> m_transportBuffer;
	std::vector<TransportOptions> m_transportOptions;
	#pragma endregion private variables

	#pragma region Logger
	const std::string FormatLog(Format logFormat, Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message) const;
	void Log(Level logLevel, const std::string& scope, const std::vector<std::string>& logPath, const std::string& message);
	void Dump(bool forced = false);
	#pragma endregion private functions for formatting a log message, logging and dumping logs
};