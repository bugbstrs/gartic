export module InputField;

import <string>;

import SelectableObject;

using String = std::string;

export class InputField : public SelectableObject
{
public:
	// Constructors
	InputField(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
			   ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight,
			   ColorType selectedBackgroungColor, ColorType selectedTextColor,
			   ConsoleManager* cm, InputManager* im,
			   SelectableObject*& selected, String& text, int maxTextLength = -1);
	InputField(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
			   ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight,
			   ColorType selectedBackgroungColor, ColorType selectedTextColor,
			   ConsoleManager* cm, InputManager* im,
			   SelectableObject*& selected, String& text, int maxTextLength = -1);
	InputField(Align horizontalAlign, Align verticalAlign,
			   ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight,
			   ColorType selectedBackgroungColor, ColorType selectedTextColor,
			   ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String &text, int maxTextLength = -1);
	
	// Destructor
	~InputField() = default;

	void Draw		() override;
	void CheckInput () override;

private:
	String& m_text;
	int     m_textPos;
	int		m_maxTextLength;

	void DrawContents() override;
};