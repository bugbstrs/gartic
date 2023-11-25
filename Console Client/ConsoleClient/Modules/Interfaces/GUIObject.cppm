export module GUIObject;

export import <Windows.h>;

export import ConsoleManager;
export import ColorType;
export import Align;

export typedef short int16_t;

export class GUIObject
{
public:
    // Constructors
    GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
              int16_t maxWidth, int16_t maxHeight);
    GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
              int16_t maxWidth, int16_t maxHeight);
    
    // Destructor
    virtual ~GUIObject() = default;
    
    // Method to override
    virtual void Draw(ConsoleManager* cm) = 0;

protected:
    Align     m_align;
    ColorType m_backgroundColor;
    ColorType m_textColor;
    COORD     m_upLeftCorner;
    int16_t   m_width;
    int16_t   m_height;
};