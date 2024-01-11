module Canvas;

Canvas::Canvas(uint64_t width, uint64_t height, ColorType color) :
	m_canvas		  { height, std::vector<Pixel>{width, Pixel{color}} },
	m_backgroundColor { color											}
{}

Canvas::Canvas(const Canvas& canvas) :
    m_canvas          { canvas.m_canvas          },
    m_backgroundColor { canvas.m_backgroundColor }
{}

void Canvas::Clear()
{
	for (auto& row : m_canvas)
		std::fill(row.begin(), row.end(), Pixel{ m_backgroundColor });
}

void Canvas::Fill(int x, int y, ColorType color)
{
    if (m_canvas[x][y].GetColor() == color)
        return;

    ColorType backgroundColor = m_canvas[x][y].GetColor();

    std::function<void(int, int)> fillRecursive = [this, backgroundColor, &fillRecursive, color](int i, int j)
    {
        if (i >= 0 && i < m_canvas.size() && j >= 0 && j < m_canvas[0].size() &&
            m_canvas[i][j].GetColor() != backgroundColor)
            return;

        m_canvas[i][j].SetColor(color);

        std::thread{ [this, color, &fillRecursive, i, j]()
        {
            fillRecursive(i - 1, j);
        } }.detach();

        std::thread{ [this, color, &fillRecursive, i, j]()
        {
            fillRecursive(i + 1, j);
        } }.detach();

        std::thread{ [this, color, &fillRecursive, i, j]()
        {
            fillRecursive(i, j - 1);
        } }.detach();

        std::thread{ [this, color, &fillRecursive, i, j]()
        {
            fillRecursive(i, j + 1);
        } }.detach();
    };
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
                At(y1 + j, x1 + i).SetColor(color);

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
            At(y2 + j, x2 + i).SetColor(color);
}

void Canvas::DrawCircle(int x, int y, ColorType color, int radius, bool filled)
{
    int i{ 0 }, j{ radius }, d{ 3 - 2 * radius };

    while (i <= j)
    {
        At(x + i, y + j).SetColor(color);
        At(x - i, y + j).SetColor(color);
        At(x + i, y - j).SetColor(color);
        At(x - i, y - j).SetColor(color);
        if (filled)
        {
            DrawLine(x - i, y - j, x - i, y + j, color, 1);
            DrawLine(x + i, y - j, x + i, y + j, color, 1);
        }
        if (i != j)
        {
            At(x + j, y + i).SetColor(color);
            At(x - j, y + i).SetColor(color);
            At(x + j, y - i).SetColor(color);
            At(x - j, y - i).SetColor(color);
            if (filled)
            {
                DrawLine(x - j, y - i, x - j, y + i, color, 1);
                DrawLine(x + j, y - i, x + j, y + i, color, 1);
            }
        }

        if (d < 0)
            d = d + 4 * i + 6;
        else
        {
            d = d + 4 * (i - j) + 10;
            --j;
        }
        ++i;
    }
}

int Canvas::GetWidth() const
{
    return m_canvas[0].size();
}

int Canvas::GetHeight() const
{
    return m_canvas.size();
}

ColorType Canvas::GetSectorColor(int x, int y, int width, int height) const
{
    if (x < 0) x = 0;
    if (x > m_canvas[0].size()) x = m_canvas[0].size();
    if (y < 0) y = 0;
    if (y > m_canvas.size()) y = m_canvas.size();
    if (x + width > m_canvas[0].size()) width = m_canvas[0].size() - x;
    if (y + height > m_canvas.size()) height = m_canvas.size() - y;

    std::unordered_map<ColorType, int> colorCount;

    for (int i{ y }; i < y + height; ++i)
        for (int j{ x }; j < x + width; ++j)
            ++colorCount[m_canvas[i][j].GetColor()];

    ColorType predominantColor;
    int maxCount{ 0 };

    for (const auto& pair : colorCount)
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            predominantColor = pair.first;
        }

    return predominantColor;
}

ColorType Canvas::GetPixelColor(int x, int y) const
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= m_canvas.size())
        x = m_canvas.size() - 1;
    if (y >= m_canvas[0].size())
        y = m_canvas[0].size() - 1;
    return m_canvas[x][y].GetColor();
}

void Canvas::SetPixelColor(int x, int y, ColorType color)
{
    if (x < 0 || x >= m_canvas.size() || y < 0 || y >= m_canvas[0].size())
        return;
    m_canvas[x][y].SetColor(color);
}

Pixel &Canvas::At(int x, int y)
{
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= m_canvas.size())
        x = m_canvas.size() - 1;
    if (y >= m_canvas[0].size())
        y = m_canvas[0].size() - 1;

    return m_canvas[x][y];
}