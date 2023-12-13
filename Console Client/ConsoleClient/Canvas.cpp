module Canvas;

Canvas::Canvas(uint64_t width, uint64_t heigth, ColorType color) :
	m_canvas		  { heigth, std::vector<Pixel>{width, Pixel{color}} },
	m_backgroundColor { color											}
{}

void Canvas::Clear()
{
	for (auto& row : m_canvas)
		std::fill(row.begin(), row.end(), Pixel{ m_backgroundColor });
}

void Canvas::DrawCircle(int x, int y, ColorType color, int radius)
{
    for (int i = 0; i <= radius; ++i)
    {
        int j = static_cast<int>(std::sqrt(radius * radius - i * i));

        m_canvas[x + i][y + j].SetColor(color);
        m_canvas[x + j][y + i].SetColor(color);
        m_canvas[x - i][y + j].SetColor(color);
        m_canvas[x - j][y + i].SetColor(color);
        m_canvas[x + i][y - j].SetColor(color);
        m_canvas[x + j][y - i].SetColor(color);
        m_canvas[x - i][y - j].SetColor(color);
        m_canvas[x - j][y - i].SetColor(color);
    }
}
