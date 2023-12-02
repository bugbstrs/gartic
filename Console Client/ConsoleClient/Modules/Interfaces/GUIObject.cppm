export module GUIObject;

export import <Windows.h>;
export import <string>;

export import ConsoleManager;
export import ColorType;
export import Align;

export using String = std::string;

export typedef short int16_t;

export class GUIObject
{
public:
    // Constructors
    GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
              int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm);
    GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
              int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm);
    GUIObject(Align align, ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
              int16_t maxHeight, ConsoleManager* cm);
    
    // Destructor
    virtual ~GUIObject() = default;
    
    // Method to override
    virtual void Draw() = 0;

    void InitializeTransform(COORD upLeftCorner);

    COORD GetUpLeftCorner();
    int16_t GetWidth     ();
    int16_t GetHeight    ();

protected:
    Align           m_align;
    ColorType       m_backgroundColor;
    ColorType       m_textColor;
    COORD           m_upLeftCorner;
    int16_t         m_width;
    int16_t         m_height;
    ConsoleManager* m_cm;

    virtual void SetColor      ();
    virtual void DrawContents  () = 0;
    void         DrawBackground();
};