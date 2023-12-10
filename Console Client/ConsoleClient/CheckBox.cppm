export module CheckBox;

import <string>;

import SelectableObject;

using String = std::string;

export class CheckBox : public SelectableObject
{
public:
	CheckBox(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, ColorType textColor,
		int16_t maxWidth, int16_t maxHeight,
		ColorType selectedBackgroungColor, ColorType selectedTextColor,
		ConsoleManager* cm, InputManager* im,
		SelectableObject*& selected, String text);
	CheckBox(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, ColorType textColor,
		int16_t maxWidth, int16_t maxHeight,
		ColorType selectedBackgroungColor, ColorType selectedTextColor,
		ConsoleManager* cm, InputManager* im,
		SelectableObject*& selected, String text);
	CheckBox(Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, ColorType textColor,
		int16_t maxWidth, int16_t maxHeight,
		ColorType selectedBackgroungColor, ColorType selectedTextColor,
		ConsoleManager* cm, InputManager* im,
		SelectableObject*& selected, String text);

	~CheckBox() = default;

	void Draw		() override;
	void CheckInput	() override;
	bool IsChecked	();

private:
	String m_text;
	bool   m_checked;

	void DrawContents() override;
};