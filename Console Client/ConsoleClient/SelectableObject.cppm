export module SelectableObject;

export import <Windows.h>;
import <functional>;

export import InputManager;
export import ColorType;
export import GUIObject;

export typedef short int16_t;

using Function = std::function<void()>;

export class SelectableObject : public GUIObject
{
public:
    // Constructors
    SelectableObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor, ConsoleManager* cm, InputManager* im,
                     SelectableObject*& selected);
    SelectableObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor, ConsoleManager* cm, InputManager* im,
                     SelectableObject*& selected);
    SelectableObject(Align align, ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
                     int16_t maxHeight, ColorType selectedBackgroundColor, ColorType selectedTextColor,
                     ConsoleManager* cm, InputManager* im, SelectableObject*& selected);

    // Destructor
    virtual ~SelectableObject() = default;

    void SetHoverColors        (ColorType background, ColorType text);
    void SetFunctionOnActivate (Function function);
    void SetConections         (SelectableObject* up, SelectableObject* down,
                                SelectableObject* left, SelectableObject* right);

    virtual void CheckInput () = 0;
    
protected:
    ColorType         m_selectedBackgroundColor;
    ColorType         m_selectedTextColor;
    ColorType         m_hoverBackgroundColor;
    ColorType         m_hoverTextColor;
    SelectableObject* m_selectedObject;
    SelectableObject* m_upObject;
    SelectableObject* m_downObject;
    SelectableObject* m_leftObject;
    SelectableObject* m_rightObject;
    InputManager*     m_im;
    Function          m_function;

    bool IsPointInside(COORD point);
};