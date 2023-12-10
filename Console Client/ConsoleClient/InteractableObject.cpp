module InteractableObject;

InteractableObject::InteractableObject(COORD upLeftCorner,
            Align horizontalAlign, Align verticalAlign,
            ColorType backgroundColor, ColorType textColor,
            int16_t maxWidth, int16_t maxHeight,
            ConsoleManager* cm, InputManager* im) :
    GUIObject              { upLeftCorner, horizontalAlign, verticalAlign, 
                             backgroundColor, textColor, maxWidth, maxHeight, cm },
    m_hoverBackgroundColor { backgroundColor                                     },
    m_hoverTextColor       { textColor                                           },
    m_im                   { im                                                  }
{}

InteractableObject::InteractableObject(int16_t x, int16_t y,
            Align horizontalAlign, Align verticalAlign,
            ColorType backgroundColor, ColorType textColor,
            int16_t maxWidth, int16_t maxHeight,
            ConsoleManager * cm, InputManager * im) :
    GUIObject              { x, y, horizontalAlign, verticalAlign, 
                             backgroundColor, textColor, maxWidth, maxHeight, cm },
    m_hoverBackgroundColor { backgroundColor                                     },
    m_hoverTextColor       { textColor                                           },
    m_im                   { im                                                  }
{}

InteractableObject::InteractableObject(Align horizontalAlign, Align verticalAlign,
            ColorType backgroundColor, ColorType textColor,
            int16_t maxWidth, int16_t maxHeight,
            ConsoleManager* cm, InputManager* im) :
    GUIObject              { horizontalAlign, verticalAlign, 
                             backgroundColor, textColor, maxWidth, maxHeight, cm },
    m_hoverBackgroundColor { backgroundColor                                     },
    m_hoverTextColor       { textColor                                           },
    m_im                   { im                                                  }
{}

void InteractableObject::SetHoverColors(ColorType background, ColorType text)
{
    m_hoverBackgroundColor = background;
    m_hoverTextColor = text;
}

bool InteractableObject::IsPointInside(COORD point)
{
    if (m_upLeftCorner.X <= point.X && m_upLeftCorner.X + m_width > point.X &&
        m_upLeftCorner.Y <= point.Y && m_upLeftCorner.Y + m_height > point.Y)
        return true;
    return false;
}

void InteractableObject::SetColor()
{
    if (IsPointInside(m_im->GetCurrentCursorPosition()))
        m_cm->SetColor(m_hoverBackgroundColor, m_hoverTextColor);
    else
        m_cm->SetColor(m_backgroundColor, m_textColor);
}