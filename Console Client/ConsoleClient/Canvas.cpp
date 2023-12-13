module Canvas;

Canvas::Canvas(uint64_t width, uint64_t height, ColorType color) :
	m_canvas		  { height, std::vector<Pixel>{width, Pixel{color}} },
	m_backgroundColor { color											}
{}

void Canvas::Clear()
{
	for (auto& row : m_canvas)
		std::fill(row.begin(), row.end(), Pixel{ m_backgroundColor });
}

void Canvas::Fill(int x, int y)
{

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

ColorType Canvas::GetPredominantColor(int x, int y, int width, int height) const
{
    if (x < 0 || y < 0 || x + width > m_canvas[0].size() || y + height > m_canvas.size())
        return ColorType::Black;

    std::unordered_map<ColorType, int> colorCount;

    for (int i{ y }; i < y + height; ++i)
        for (int j{ x }; j < x + width; ++j)
            colorCount[m_canvas[i][j].GetColor()]++;

    ColorType predominantColor;
    int maxCount = 0;

    for (const auto& pair : colorCount)
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            predominantColor = pair.first;
        }

    return predominantColor;
}
