module CheckBox;

CheckBox::CheckBox(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
			       ColorType backgroundColor, ColorType textColor,
			       int16_t maxWidth, int16_t maxHeight,
			       ColorType selectedBackgroungColor, ColorType selectedTextColor,
			       ConsoleManager *cm, InputManager *im,
			       SelectableObject *&selected, String text) :
	SelectableObject { upLeftCorner, horizontalAlign, verticalAlign,
					   backgroundColor, textColor, maxWidth,
					   maxHeight, selectedBackgroungColor, selectedTextColor,
					   cm, im, selected										 },
	m_text			 { text													 }
{}

CheckBox::CheckBox(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
				   ColorType backgroundColor, ColorType textColor,
				   int16_t maxWidth, int16_t maxHeight,
				   ColorType selectedBackgroungColor, ColorType selectedTextColor,
				   ConsoleManager *cm, InputManager *im,
				   SelectableObject *&selected, String text):
	SelectableObject { x, y, horizontalAlign, verticalAlign, backgroundColor,
					   textColor, maxWidth, maxHeight, selectedBackgroungColor,
					   selectedTextColor, cm, im, selected					   },
	m_text			 { text													   }
{}

CheckBox::CheckBox(Align horizontalAlign, Align verticalAlign,
				   ColorType backgroundColor, ColorType textColor,
				   int16_t maxWidth, int16_t maxHeight,
				   ColorType selectedBackgroungColor, ColorType selectedTextColor,
				   ConsoleManager *cm, InputManager *im,
				   SelectableObject *&selected, String text):
	SelectableObject { horizontalAlign, verticalAlign, backgroundColor,
					   textColor, maxWidth, maxHeight, selectedBackgroungColor,
					   selectedTextColor, cm, im, selected					   },
	m_text			 { text													   }
{}
