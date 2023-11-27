export module Label;

import <string>;

import GUIObject;

using String = std::string;

export class Label : public GUIObject
{
public:
	// Constructors
	Label(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
		  int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, String text);
	Label(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
		  int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, String text);

	// Destructor
	~Label() = default;

	void Draw() override;

private:
	String m_text;
};