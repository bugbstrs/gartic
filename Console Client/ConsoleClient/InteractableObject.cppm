export module InteractableObject;

export import InputManager;
export import ColorType;
export import GUIObject;

export typedef short int16_t;

export class InteractableObject : public GUIObject
{
public:
    InteractableObject(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
                       ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
                       int16_t maxHeight, ConsoleManager* cm, InputManager* im);
    InteractableObject(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
                       ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
                       int16_t maxHeight, ConsoleManager* cm, InputManager* im);
    InteractableObject(Align horizontalAlign, Align verticalAlign,
                       ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
                       int16_t maxHeight, ConsoleManager* cm, InputManager* im);

	virtual ~InteractableObject() = default;

    void         SetHoverColors (ColorType background, ColorType text);
    void         CheckCursor    ();
    virtual void CheckInput     () = 0;

private:
    ColorType     m_hoverBackgroundColor;
    ColorType     m_hoverTextColor;
    InputManager* m_im;

    bool IsPointInside (COORD point);
    void SetColor      () override;
};