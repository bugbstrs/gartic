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
    return std::format("{}: {}, {}, {}", "Fill", m_x, m_y, m_color);
}

void http::Fill::Deserialize(const std::string& toDeserialize)
{
    std::istringstream iss(toDeserialize);

    int x, y, color;

    iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');

    iss >> x >> y >> color;

    if (!iss.fail()) 
    {
        m_x = x;
        m_y = y;
        m_color = color;
    }
}
