#include "Clear.h"

using namespace http;

const std::string& http::Clear::Serialize()
{
    return std::format("{}", "Clear");
}

void http::Clear::Deserialize(const std::string&)
{
}
