module SelectableObject;

SelectableObject::SelectableObject(COORD upLeftCorner, Align align, ColorType backgroundColor,
                                   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor,
                                   ColorType selectedTextColor, SelectableObject*& selected) :
    GUIObject                 { upLeftCorner, align, backgroundColor, textColor, maxWidth, maxHeight },
	m_selectedBackgroundColor { selectedBackgroundColor                                              },
	m_selectedTextColor		  { selectedTextColor		                                             },
    m_selectedObject          { selected                                                             },
    m_hoverBackgroundColor    { backgroundColor                                                      },
    m_hoverTextColor          { textColor                                                            }
{}

SelectableObject::SelectableObject(int16_t x, int16_t y, Align align, ColorType backgroundColor,
                                   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor,
                                   ColorType selectedTextColor, SelectableObject*& selected) :
    GUIObject                 { x, y, align, backgroundColor, textColor, maxWidth, maxHeight },
    m_selectedBackgroundColor { selectedBackgroundColor                                      },
    m_selectedTextColor       { selectedTextColor                                            },
    m_selectedObject          { selected                                                     },
    m_hoverBackgroundColor    { backgroundColor                                              },
    m_hoverTextColor          { textColor                                                    }
{}

SelectableObject::SelectableObject(Align align, ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor, ColorType selectedTextColor,
                                   SelectableObject * &selected) :
    GUIObject                 { align, backgroundColor, textColor, maxWidth, maxHeight },
    m_selectedBackgroundColor { selectedBackgroundColor                                },
    m_selectedTextColor       { selectedTextColor                                      },
    m_selectedObject          { selected                                               },
    m_hoverBackgroundColor    { backgroundColor                                        },
    m_hoverTextColor          { textColor                                              }
{}

void SelectableObject::SetHoverColors(ColorType background, ColorType text)
{
    m_hoverBackgroundColor = background;
    m_hoverTextColor       = text;
}

void SelectableObject::SetConections(SelectableObject* up, SelectableObject* down,
                                     SelectableObject* left, SelectableObject* right)
{
    m_upObject    = up;
    m_downObject  = down;
    m_leftObject  = left;
    m_rightObject = right;
}

void SelectableObject::CheckInput(InputManager* im)
{
    if (this == m_selectedObject)
    {
        
    }
}

bool SelectableObject::IsPointInside(COORD point)
{
    if (m_upLeftCorner.X >= point.X && m_upLeftCorner.X + m_width < point.X &&
        m_upLeftCorner.Y >= point.Y && m_upLeftCorner.Y + m_height < point.Y)
        return true;
    return false;
}
