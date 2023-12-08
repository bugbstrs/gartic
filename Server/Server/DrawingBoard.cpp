#include "DrawingBoard.h"

using namespace http;

std::vector<std::pair<std::string, std::vector<DrawEvent>>> http::DrawingBoard::GetEvents() const noexcept
{
    return m_events;
}

void http::DrawingBoard::Fill(int x, int y, Color color)
{
}

void http::DrawingBoard::Draw(int x, int y, Color color, int width)
{
}
