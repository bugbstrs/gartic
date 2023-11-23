#include "HttpUtils.h"

using namespace http;

std::vector<String> http::Split(const String& str, const String& delim)
{
    std::vector<String> result;
    size_t startIndex = 0;

    for (size_t found = str.find(delim); found != String::npos; found = str.find(delim, startIndex))
    {
        result.emplace_back(str.begin() + startIndex, str.begin() + found);
        startIndex = found + delim.size();
    }

    if (startIndex != str.size())
    {
        result.emplace_back(str.begin() + startIndex, str.end());
    }

    return result;
}

StringMap http::ParseUrlArgs(const String& urlArgs)
{
    if (urlArgs == "") 
    {
        return {};
    }

    StringMap result;
    for (const auto& kvStr : Split(urlArgs, "&")) 
    {
        auto kvVector = Split(kvStr, "=");
        
        if (kvVector.size() == 2)
        {
            result[kvVector[0]] = kvVector[1];
        }
    }

    return result;
}
