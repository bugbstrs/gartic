module SelectableObject;

SelectableObject::SelectableObject(COORD upLeftCorner, Align align, ColorType backgroundColor,
                                   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor,
                                   ColorType selectedTextColor, SelectableObject*& selected) :
    GUIObject                 { upLeftCorner, align, backgroundColor, textColor, maxWidth, maxHeight },
	m_selectedBackgroundColor { selectedBackgroundColor                                              },
	m_selectedTextColor		  { selectedTextColor		                                             },
    m_selectedObject          { selected                                                             }
{}

SelectableObject::SelectableObject(int16_t x, int16_t y, Align align, ColorType backgroundColor,
                                   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
                                   ColorType selectedBackgroundColor,
                                   ColorType selectedTextColor, SelectableObject*& selected) :
    GUIObject                 { x, y, align, backgroundColor, textColor, maxWidth, maxHeight },
    m_selectedBackgroundColor { selectedBackgroundColor                                      },
    m_selectedTextColor       { selectedTextColor                                            },
    m_selectedObject          { selected                                                     }
{}

bool SelectableObject::IsPointInside(COORD point)
{
    if (m_upLeftCorner.X >= point.X && m_upLeftCorner.X + m_width < point.X &&
        m_upLeftCorner.Y >= point.Y && m_upLeftCorner.Y + m_height < point.Y)
        return true;
    return false;
}

bool SelectableObject::IsPointInside(int16_t x, int16_t y)
{
    if (m_upLeftCorner.X >= x && m_upLeftCorner.X + m_width < x &&
        m_upLeftCorner.Y >= y && m_upLeftCorner.Y + m_height < y)
        return true;
    return false;
}