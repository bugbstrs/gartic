#include "DrawEvent.h"

CanvasPoints http::DrawEvent::GetCanvasPoints() const noexcept
{
    return m_canvasPoints;
}

int http::DrawEvent::GetX() const noexcept
{
    return m_x;
}

int http::DrawEvent::GetY() const noexcept
{
    return m_y;
}

Color http::DrawEvent::GetColor() const noexcept
{
    return m_color;
}

int http::DrawEvent::GetWidth() const noexcept
{
    return m_width;
}

void http::DrawEvent::SetX(int newX)
{
    m_x = newX;
}

void http::DrawEvent::SetY(int newY)
{
    m_y = newY;
}

void http::DrawEvent::SetColor(Color newColor)
{
    m_color = newColor;
}

void http::DrawEvent::SetWidth(int newWidth)
{
    m_width = newWidth;
}
