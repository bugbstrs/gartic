module SelectableObject;

SelectableObject::SelectableObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, ColorType selectedBackgroundColor, ColorType selectedTextColor):
    GUIObject                 { upLeftCorner, align, backgroundColor, textColor, maxWidth },
	m_selectedBackgroundColor { selectedBackgroundColor                                    },
	m_selectedTextColor		  { selectedTextColor		                                   }
{}

SelectableObject::SelectableObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
                                   int16_t maxWidth, ColorType selectedBackgroundColor, ColorType selectedTextColor):
    GUIObject                 { x, y, align, backgroundColor, textColor, maxWidth },
    m_selectedBackgroundColor { selectedBackgroundColor                            },
    m_selectedTextColor       { selectedTextColor                                  }
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