export module Button;

import <string>;

import SelectableObject;

using String = std::string;

export class Button : public SelectableObject
{
public:
	// Constructors
	Button(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
		   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
		   ColorType selectedTextColor, ConsoleManager *cm, InputManager *im,
		   SelectableObject *&selected, String text);
	Button(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
		   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
		   ColorType selectedTextColor, ConsoleManager *cm, InputManager *im,
		   SelectableObject *&selected, String text);
	Button(Align align, ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
		   int16_t maxHeight, ColorType selectedBackgroungColor, ColorType selectedTextColor,
		   ConsoleManager *cm, InputManager *im, SelectableObject *&selected, String text);

	// Destructor
	~Button() = default;

	void Draw		() override;
	void CheckInput () override;

private:
	String m_text;

	void DrawContents() override;
};