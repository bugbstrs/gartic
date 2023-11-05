export module TransportOptions;
import LogLevel;
import LogFormat;
import <cstdint>;
import <string>;

export struct TransportOptions
{
	LogLevel minLevel;
	LogLevel maxLevel;
	LogFormat logFormat;
	unsigned int bufferSize = 25;
	std::string filePath;
};
