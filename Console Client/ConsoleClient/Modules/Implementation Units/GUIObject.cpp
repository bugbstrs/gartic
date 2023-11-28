module GUIObject;

GUIObject::GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm):
    m_upLeftCorner    { upLeftCorner    },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       },
    m_cm              { cm              }
{}

GUIObject::GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm):
    m_upLeftCorner    { x, y            },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       },
    m_cm              { cm              }
{}

GUIObject::GUIObject(Align align, ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
                     int16_t maxHeight, ConsoleManager* cm) :
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       },
    m_cm              { cm              }
{}

void GUIObject::InitializeTransform(COORD upLeftCorner)
{
    m_upLeftCorner = upLeftCorner;
}

COORD GUIObject::GetUpLeftCorner()
{
    return m_upLeftCorner;
}

int16_t GUIObject::GetWidth()
{
    return m_width;
}

int16_t GUIObject::GetHeight()
{
    return m_height;
}