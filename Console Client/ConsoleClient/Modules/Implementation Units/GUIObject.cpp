module GUIObject;

GUIObject::GUIObject(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
                     ColorType textColor, int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm):
    m_upLeftCorner    { upLeftCorner    },
    m_horizontalAlign { horizontalAlign },
    m_verticalAlign   { verticalAlign   },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       },
    m_cm              { cm              }
{}

GUIObject::GUIObject(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
                     ColorType textColor, int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm):
    m_upLeftCorner    { x, y            },
    m_horizontalAlign { horizontalAlign },
    m_verticalAlign   { verticalAlign   },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       },
    m_cm              { cm              }
{}

GUIObject::GUIObject(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm) :
    m_horizontalAlign { horizontalAlign },
    m_verticalAlign   { verticalAlign   },
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

void GUIObject::SetColor()
{
    m_cm->SetColor(m_backgroundColor, m_textColor);
}

void GUIObject::DrawBackground()
{
    String s(m_width * m_height, ' ');
    m_cm->Write(s, m_upLeftCorner.X, m_upLeftCorner.Y,
                m_width, m_height, m_horizontalAlign, m_verticalAlign);
}
