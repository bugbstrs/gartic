#include "StartDraw.h"

using namespace http;

http::StartDraw::StartDraw(int newX, int newY, int newWidth, int newColor):
    m_x{newX},
    m_y{newY},
    m_width{newWidth},
    m_color{newColor}
{
}

const std::string& http::StartDraw::Serialize()
{
    return std::format("{}: {}, {}, {}, {}", "StartDraw", m_x, m_y, m_width, m_color);
}

void http::StartDraw::Deserialize(const std::string& toDeserialize)
{
    std::istringstream iss(toDeserialize);

    int x, y, width, color;

    iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');

    iss >> x >> y >> width >> color;

    if (!iss.fail())
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_color = color;
    }
}
