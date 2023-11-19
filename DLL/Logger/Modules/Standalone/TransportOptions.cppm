export module TransportOptions;
import LogLevel;
import LogFormat;
import <string>;

export struct TransportOptions
{
	LogLevel minLevel       = LogLevel::INFO;
	LogLevel maxLevel       = LogLevel:: FATAL;
	LogFormat logFormat     = LogFormat::TEXT;
	unsigned int bufferSize = 25;
	std::string filePath    = "log.txt";
};
