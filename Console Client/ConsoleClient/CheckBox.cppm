export module CheckBox;

import <string>;

import SelectableObject;

using String = std::string;

export class CheckBox : public SelectableObject
{
public:
	CheckBox(COORD upLeftCorner,
		ColorType backgroundColor, ColorType checkColor,
		ColorType selectedColor, int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, InputManager* im, SelectableObject*& selected);
	CheckBox(int16_t x, int16_t y,
		ColorType backgroundColor, ColorType checkColor,
		ColorType selectedColor, int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, InputManager* im, SelectableObject*& selected);
	CheckBox(ColorType backgroundColor, ColorType checkColor,
		ColorType selectedColor, int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, InputManager* im, SelectableObject*& selected);

	~CheckBox() = default;

	void Draw			() override;
	void CheckInput		() override;
	void SetHoverColors	(ColorType background, ColorType text) override;
	bool IsChecked		();

private:
	bool	  m_checked;
	ColorType m_checkColor;

	void DrawContents() override;
};