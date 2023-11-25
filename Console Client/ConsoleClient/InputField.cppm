export module InputField;

import <string>;

import SelectableObject;

using String = std::string;

export class InputField : public SelectableObject
{
public:
	// Constructors
	InputField(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
			   ColorType selectedTextColor, SelectableObject*& selected, String& text);
	InputField(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
			   ColorType selectedTextColor, SelectableObject*& selected, String& text);
	
	// Destructor
	~InputField() = default;

	void Draw(ConsoleManager* cm) override;
private:
	String m_text;
};