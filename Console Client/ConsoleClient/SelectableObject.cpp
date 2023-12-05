module SelectableObject;

SelectableObject::SelectableObject(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
                                   ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   ConsoleManager* cm, InputManager* im, SelectableObject*& selected) :
    GUIObject                 { upLeftCorner, horizontalAlign, verticalAlign, 
                                backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_selectedBackgroundColor { selectedBackgroundColor                             },
	m_selectedTextColor		  { selectedTextColor		                            },
    m_selectedObject          { selected                                            },
    m_hoverBackgroundColor    { backgroundColor                                     },
    m_hoverTextColor          { textColor                                           },
    m_im                      { im                                                  }
{}

SelectableObject::SelectableObject(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
                                   ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   ConsoleManager* cm, InputManager* im, SelectableObject*& selected) :
    GUIObject                 { x, y, horizontalAlign, verticalAlign, backgroundColor,
                                textColor, maxWidth, maxHeight, cm                     },
    m_selectedBackgroundColor { selectedBackgroundColor                                },
    m_selectedTextColor       { selectedTextColor                                      },
    m_selectedObject          { selected                                               },
    m_hoverBackgroundColor    { backgroundColor                                        },
    m_hoverTextColor          { textColor                                              },
    m_im                      { im                                                     }
{}

SelectableObject::SelectableObject(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
                                   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   ConsoleManager* cm, InputManager* im, SelectableObject*& selected) :
    GUIObject                 { horizontalAlign, verticalAlign, backgroundColor,
                                textColor, maxWidth, maxHeight, cm               },
    m_selectedBackgroundColor { selectedBackgroundColor                          },
    m_selectedTextColor       { selectedTextColor                                },
    m_selectedObject          { selected                                         },
    m_hoverBackgroundColor    { backgroundColor                                  },
    m_hoverTextColor          { textColor                                        },
    m_im                      { im                                               }
{}

void SelectableObject::SetHoverColors(ColorType background, ColorType text)
{
    m_hoverBackgroundColor = background;
    m_hoverTextColor       = text;
}

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
        m_im->GetClickPressed())
    {
        m_selectedObject = this;
        if (m_function)
            m_function();
    }
}

bool SelectableObject::IsPointInside(COORD point)
{
    if (m_upLeftCorner.X <= point.X && m_upLeftCorner.X + m_width > point.X &&
        m_upLeftCorner.Y <= point.Y && m_upLeftCorner.Y + m_height > point.Y)
        return true;
    return false;
}

void SelectableObject::SetColor()
{
    if (this == m_selectedObject)
        m_cm->SetColor(m_selectedBackgroundColor, m_selectedTextColor);
    else
    {
        if (IsPointInside(m_im->GetCurrentCursorPosition()))
            m_cm->SetColor(m_hoverBackgroundColor, m_hoverTextColor);
        else
            m_cm->SetColor(m_backgroundColor, m_textColor);
    }
}
