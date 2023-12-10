export module SpinBox;

import <string>;
import <vector>;

import InteractableObject;
import SelectableObject;
import InputManager;
import Button;

using String = std::string;
using Options = std::vector<String>;

export class SpinBox : public InteractableObject
{
public:
	// Constructors
	SpinBox(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, ColorType textColor,
		int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, InputManager* im, SelectableObject*& selected,
		ColorType buttonsBackgroundColor, ColorType buttonsTextColor,
		ColorType buttonsSelectedBackgroungColor, ColorType buttonsSelectedTextColor);
	SpinBox(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, ColorType textColor,
		int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, InputManager* im, SelectableObject*& selected,
		ColorType buttonsBackgroundColor, ColorType buttonsTextColor,
		ColorType buttonsSelectedBackgroungColor, ColorType buttonsSelectedTextColor);
	SpinBox(Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, ColorType textColor,
		int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, InputManager* im, SelectableObject*& selected,
		ColorType buttonsBackgroundColor, ColorType buttonsTextColor,
		ColorType buttonsSelectedBackgroungColor, ColorType buttonsSelectedTextColor);

	// Destructor
	~SpinBox();

	void			  SetOptions		 (Options options, int startOption);
	void			  Draw				 () override;
	void			  InitializeTransform(COORD upLeftCorner) override;
	void			  CheckCursor		 () override;
	String			  GetOption			 () const;
	SelectableObject* GetNextButton		 () const;
	SelectableObject* GetPreviousButton	 () const;

private:
	Options m_options;
	Button* m_right;
	Button* m_left;
	int     m_optionSelected;

	void DrawContents	() override;
	void PreviousOption	();
	void NextOption		();
};