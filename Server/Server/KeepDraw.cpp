#include "KeepDraw.h"

using namespace http;

http::KeepDraw::KeepDraw(int newX, int newY) :
    m_x{ newX },
    m_y{ newY }
{
}

const std::string& http::KeepDraw::Serialize()
{
    return std::format("{} {} {}", "KeepDraw", m_x, m_y);
}
