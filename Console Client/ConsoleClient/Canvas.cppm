export module Canvas;

import <vector>;

export import ColorType;
import Pixel;

export class Canvas
{
public:
	Canvas(int width, int heigth, ColorType color);

	~Canvas() = default;

	void Clear();
	void Fill(int x, int y);
	void DrawCircle(int x, int y, ColorType color, int radious);
	ColorType GetPredominantColor(int x, int y, int width, int heigth) const;

private:
	std::vector<std::vector<Pixel>> m_canvas;
};