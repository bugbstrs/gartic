export module ColorDisplay;

import GUIObject;

export class ColorDisplay : public GUIObject
{
public:
	ColorDisplay(COORD upLeftCorner, ColorType color,
				 int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm);
	ColorDisplay(int16_t x, int16_t y, ColorType color,
				 int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm);
	ColorDisplay(ColorType color, int16_t maxWidth, int16_t maxHeight,
				 ConsoleManager *cm);

	~ColorDisplay() = default;

	void SetDisplayColor(ColorType color);

	void Draw() override;

private:
	void DrawContents() override;
};