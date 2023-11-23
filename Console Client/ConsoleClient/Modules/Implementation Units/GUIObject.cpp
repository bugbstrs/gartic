module GUIObject;

GUIObject::GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor, int16_t max_width):
    m_upLeftCorner    { upLeftCorner    },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { max_width       }
{}

GUIObject::GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor, int16_t max_width):
    m_upLeftCorner    { x, y            },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { max_width       }
{}