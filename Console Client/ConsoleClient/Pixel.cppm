export module Pixel;

export import ColorType;

export class Pixel
{
public:
	Pixel(ColorType color);

	~Pixel() = default;

	void	  SetColor(ColorType color);
	ColorType GetColor() const;

private:
	ColorType m_color;
};