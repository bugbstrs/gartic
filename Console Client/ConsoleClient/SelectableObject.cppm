export module SelectableObject;

import <functional>;

export import InputManager;
export import ColorType;
export import GUIObject;

export typedef short int16_t;

export using Function = std::function<void(std::string)>;

export class SelectableObject : public GUIObject
{
public:
    // Constructors
    SelectableObject(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
                     ColorType textColor, int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor, ConsoleManager* cm, InputManager* im,
                     SelectableObject*& selected);
    SelectableObject(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
                     ColorType textColor, int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor, ConsoleManager* cm, InputManager* im,
                     SelectableObject*& selected);
    SelectableObject(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor, ColorType textColor,
                     int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroundColor,
                     ColorType selectedTextColor,ConsoleManager* cm, InputManager* im, SelectableObject*& selected);

    // Destructor
    virtual ~SelectableObject() = default;

    virtual void SetHoverColors (ColorType background, ColorType text);
    virtual void SetFunctionOnActivate (Function function, std::string argument = "");
    virtual void SetConections  (SelectableObject* up, SelectableObject* down,
                                 SelectableObject* left, SelectableObject* right);
    virtual void CheckInput     () = 0;
    virtual void CheckCursor    ();
    void CanBeSelected          (bool selectable);
    bool IsSelectable           ();
    
protected:
    bool               m_selectable;
    Function           m_function;
    std::string        m_argument;
    ColorType          m_selectedBackgroundColor;
    ColorType          m_selectedTextColor;
    ColorType          m_hoverBackgroundColor;
    ColorType          m_hoverTextColor;
    InputManager*      m_im;
    SelectableObject*  m_upObject;
    SelectableObject*  m_downObject;
    SelectableObject*  m_leftObject;
    SelectableObject*  m_rightObject;
    SelectableObject*& m_selectedObject;

    bool IsPointInside (COORD point);
    void SetColor      () override;
};