module GUIObject;

GUIObject::GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight):
    m_upLeftCorner    { upLeftCorner    },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       }
{}

GUIObject::GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight):
    m_upLeftCorner    { x, y            },
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       }
{}

GUIObject::GUIObject(Align align, ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
                     int16_t maxHeight) :
    m_align           { align           },
    m_backgroundColor { backgroundColor },
    m_textColor       { textColor       },
    m_width           { maxWidth        },
    m_height          { maxHeight       }
{}

void GUIObject::InitializeTransform(COORD upLeftCorner, int16_t maxWidth, int16_t maxHeight)
{
    m_upLeftCorner = upLeftCorner;
    m_width =        maxWidth;
    m_height =       maxHeight;
}
