export module Label;

import <string>;

import GUIObject;

using String = std::string;

export class Label : public GUIObject
{
public:
	// Constructors
	Label(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
		  ColorType textColor, int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, String text);
	Label(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
		  ColorType textColor, int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm, String text);
	Label(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor, ColorType textColor,
		  int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm, String text);

	// Destructor
	~Label() = default;

	void UpdateText	(const String &text);
	void Draw		() override;

private:
	String m_text;

	void DrawContents() override;
};