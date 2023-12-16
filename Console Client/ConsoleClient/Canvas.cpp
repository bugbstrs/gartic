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

void Canvas::Fill(int x, int y, ColorType color)
{

}

void Canvas::DrawLine(int x1, int y1, int x2, int y2, ColorType color, int width)
{
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2)
    {
        for (int i = -width / 2; i < width / 2; ++i)
            for (int j = -width / 2; j < width / 2; ++j)
                m_canvas[x1 + i][y1 + j].SetColor(color);

        int err2 = 2 * err;
        if (err2 > -dy) 
        {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }

    for (int i = -width / 2; i < width / 2; ++i)
        for (int j = -width / 2; j < width / 2; ++j)
            m_canvas[x2 + i][y2 + j].SetColor(color);
}

void Canvas::DrawCircle(int x, int y, ColorType color, int radius, bool filled)
{
    int i{ 0 }, j{ radius }, d{ 3 - 2 * radius };
    std::vector<std::pair<int, int>> fillCoordonates{ d };

    while (i < j)
    {
        m_canvas[x + i][y + j].SetColor(color);
        m_canvas[x - i][y + j].SetColor(color);
        m_canvas[x + i][y - j].SetColor(color);
        m_canvas[x - i][y - j].SetColor(color);
        m_canvas[x + j][y + i].SetColor(color);
        m_canvas[x - j][y + i].SetColor(color);
        m_canvas[x + j][y - i].SetColor(color);
        m_canvas[x - j][y - i].SetColor(color);

        if (d < 0)
            d = d + 4 * i + 6;
        else
        {
            d = d + 4 * (i - j) + 10;
            j--;
        }
        i++;

        if (i <= j)
        {
            m_canvas[x + i][y + j].SetColor(color);
            m_canvas[x - i][y + j].SetColor(color);
            m_canvas[x + i][y - j].SetColor(color);
            m_canvas[x - i][y - j].SetColor(color);

            if (i != j)
            {
                m_canvas[x + i][y + j].SetColor(color);
                m_canvas[x - i][y + j].SetColor(color);
                m_canvas[x + i][y - j].SetColor(color);
                m_canvas[x - i][y - j].SetColor(color);
            }
        }
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
