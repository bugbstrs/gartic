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
	using Format               = LogFormat;
	using Level                = LogLevel;
	using Path                 = std::vector<std::string>;
	using String               = std::string;
	using TransportOptions     = TransportOptions;
	using TransportBuffer      = std::vector<std::vector<std::string>>;
	using TransportOptionsVect = std::vector<TransportOptions>;
	#pragma endregion using statements for TransportOptions, LogFormat & LogLevel

	#pragma region Logger
	Logger(const TransportOptionsVect& transportOptions);
	~Logger();
	#pragma endregion constructors and destructor

	#pragma region Logger
	void Error (const String& scope, const Path& path, const String& message);
	void Fatal (const String& scope, const Path& path, const String& message);
	void Info  (const String& scope, const Path& path, const String& message);
	void Warn  (const String& scope, const Path& path, const String& message);
	#pragma endregion logging functions for the 4 levels: info/warn/error/fatal
	
	#pragma region Logger
	void ForceDump();
	#pragma endregion other functions

	#pragma region Logger
	static const std::string ConvertLogLevelToEmoji(Level level);
	static const std::string ConvertLogLevelToString(Level level);
	#pragma endregion static members (converting log levels to emoji/string)
private:
	#pragma region Logger
	TransportBuffer	     m_transportBuffer;
	TransportOptionsVect m_transportOptions;
	#pragma endregion private variables

	#pragma region Logger
	const String FormatLog(Format logFormat, Level logLevel, const String& scope, const Path& logPath, const String& message) const;
	void		 Dump(bool forced = false);
	void		 Log(Level logLevel, const String& scope, const Path& logPath, const String& message);
	#pragma endregion private functions for formatting a log message, logging and dumping logs
};