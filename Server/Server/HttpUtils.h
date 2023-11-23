#pragma once
#include<vector>;
#include<string>;
#include<unordered_map>;

using String = std::string;
using StringMap = std::unordered_map<String, String>;

namespace http
{
	std::vector<String> Split(const String& str, const String& delim);

	StringMap ParseUrlArgs(const String& urlArgs);
}