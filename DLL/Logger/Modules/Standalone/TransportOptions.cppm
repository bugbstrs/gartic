export module TransportOptions;

import LogFormat;
import LogLevel;

import <string>;

export struct TransportOptions
{
    LogLevel     minLevel   = LogLevel::INFO;
    LogLevel     maxLevel   = LogLevel:: FATAL;
    LogFormat    logFormat  = LogFormat::TEXT;
    unsigned int bufferSize = 25;
    std::string  filePath   = "log.txt";
};
