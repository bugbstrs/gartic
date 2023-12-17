export module Canvas;

import <functional>;
import <cstdint>;
import <vector>;
import <thread>;

export import ColorType;
import Pixel;

export class Canvas
{
public:
	Canvas(uint64_t width, uint64_t height, ColorType color);

	~Canvas() = default;

	void	  Clear			();
	void	  Fill			(int x, int y, ColorType color);
	void	  DrawLine		(int x1, int y1, int x2, int y2, ColorType color, int width);
	void	  DrawCircle	(int x, int y, ColorType color, int radius, bool filled = true);
	int		  GetWidth		() const;
	int		  GetHeight		() const;
	ColorType GetSectorColor(int x, int y, int width, int height) const;

private:
	std::vector<std::vector<Pixel>> m_canvas;
	ColorType m_backgroundColor;
};