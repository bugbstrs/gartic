#include "KeepDraw.h"

using namespace http;

http::KeepDraw::KeepDraw(int newX, int newY) :
    m_x{ newX },
    m_y{ newY }
{
}

const std::string& http::KeepDraw::Serialize()
{
    return std::format("{}: {}, {}", "KeepDraw", m_x, m_y);
}

void http::KeepDraw::Deserialize(const std::string& toDeserialize)
{
    std::istringstream iss(toDeserialize);

    int x, y;

    iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');

    iss >> x >> y;

    if (!iss.fail()) 
    {
        m_x = x;
        m_y = y;
    }
}
