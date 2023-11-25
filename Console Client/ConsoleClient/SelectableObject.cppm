export module SelectableObject;

export import <Windows.h>;

export import ColorType;
export import GUIObject;

export typedef short int16_t;

export class SelectableObject : public GUIObject
{
public:
    // Constructors
    SelectableObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor, SelectableObject*& selected);
    SelectableObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor, SelectableObject*& selected);

    // Destructor
    virtual ~SelectableObject() = default;

    // Position
    bool IsPointInside(COORD point);
    bool IsPointInside(int16_t x, int16_t y);

protected:
    ColorType         m_selectedBackgroundColor;
    ColorType         m_selectedTextColor;
    SelectableObject* m_selectedObject;
};