#include "Undo.h"

using namespace http;

const std::string& http::Undo::Serialize()
{
    return std::format("{}", "Undo");
}