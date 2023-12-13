module Pixel;

Pixel::Pixel(ColorType color) :
	m_color{color}
{}

void Pixel::SetColor(ColorType color)
{
	m_color = color;
}

ColorType Pixel::GetColor() const
{
	return m_color;
}
