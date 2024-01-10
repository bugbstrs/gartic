#include "Fill.h"

using namespace http;

http::Fill::Fill(int newX, int newY, int newColor) :
    m_x{ newX },
    m_y{ newY },
    m_color{ newColor }
{
}

const std::string& http::Fill::Serialize()
{
    return std::format("{} {} {} {}", "Fill", m_x, m_y, m_color);
}