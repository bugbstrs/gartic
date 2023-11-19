module GUIObject;

GUIObject::GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor, uint16_t width):
    m_upLeftCorner    { upLeftCorner    },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { width           }
{}

GUIObject::GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor, uint16_t width):
    m_upLeftCorner    { x, y            },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { width           }
{}
