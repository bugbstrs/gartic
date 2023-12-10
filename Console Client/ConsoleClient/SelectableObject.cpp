module SelectableObject;

SelectableObject::SelectableObject(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
                                   ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   ConsoleManager* cm, InputManager* im, SelectableObject*& selected) :
    InteractableObject        { upLeftCorner, horizontalAlign, verticalAlign, 
                                backgroundColor, textColor, maxWidth, maxHeight, cm, im },
	m_selectedBackgroundColor { selectedBackgroundColor                                 },
	m_selectedTextColor		  { selectedTextColor		                                },
    m_selectedObject          { selected                                                },
    m_selectable              { true                                                    }
{}

SelectableObject::SelectableObject(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
                                   ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   ConsoleManager* cm, InputManager* im, SelectableObject*& selected) :
    InteractableObject        { x, y, horizontalAlign, verticalAlign, backgroundColor,
                                textColor, maxWidth, maxHeight, cm, im                 },
    m_selectedBackgroundColor { selectedBackgroundColor                                },
    m_selectedTextColor       { selectedTextColor                                      },
    m_selectedObject          { selected                                               },
    m_selectable              { true                                                   }
{}

SelectableObject::SelectableObject(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
                                   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   ConsoleManager* cm, InputManager* im, SelectableObject*& selected) :
    InteractableObject        { horizontalAlign, verticalAlign, backgroundColor,
                                textColor, maxWidth, maxHeight, cm, im           },
    m_selectedBackgroundColor { selectedBackgroundColor                          },
    m_selectedTextColor       { selectedTextColor                                },
    m_selectedObject          { selected                                         },
    m_selectable              { true                                             }
{}

void SelectableObject::SetFunctionOnActivate(Function function)
{
    m_function = function;
}

void SelectableObject::SetConections(SelectableObject* up, SelectableObject* down,
                                     SelectableObject* left, SelectableObject* right)
{
    m_upObject    = up;
    m_downObject  = down;
    m_leftObject  = left;
    m_rightObject = right;
}

void SelectableObject::CheckCursor()
{
    if (IsPointInside(m_im->GetCurrentCursorPosition()) &&
        m_im->GetClickPressed() && m_selectable)
    {
        m_selectedObject = this;
        if (m_function)
            m_function();
    }
}

void SelectableObject::CanBeSelected(bool selectable)
{
    m_selectable = selectable;
}

bool SelectableObject::IsSelectable()
{
    return m_selectable;
}

void SelectableObject::SetColor()
{
    if (this == m_selectedObject)
        m_cm->SetColor(m_selectedBackgroundColor, m_selectedTextColor);
    else
    {
        if (IsPointInside(m_im->GetCurrentCursorPosition()) && m_selectable)
            m_cm->SetColor(m_hoverBackgroundColor, m_hoverTextColor);
        else
            m_cm->SetColor(m_backgroundColor, m_textColor);
    }
}
