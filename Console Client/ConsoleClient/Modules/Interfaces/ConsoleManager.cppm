export module ConsoleManager;

export import ColorType;
import ConsoleBuffer;
import Align;

using String = std::string;
using WString = std::wstring;

export class ConsoleManager
{
public:
	// Constructors
	ConsoleManager();

	// Destructor
	~ConsoleManager();

	// Setters
	void NewConsole			(const LPCWSTR title, int16_t width, int16_t height);
	void SetConsoleFont		(const WString fontName, int16_t width, int16_t height);
	void SetTextColor		(ColorType color);
	void SetBackgroundColor (ColorType color);
	void SetColor			(ColorType background, ColorType text);
	void SetCursor			(bool visible, COORD coord = { 0,0 });
	void SetCursor			(bool visible, int16_t x, int16_t y);
	void ToggleFullscreen	();

	// Output related
	void WriteHorizontal (const String& sentence, int16_t x, int16_t y);
	void WriteHorizontal (const WString& sentence, int16_t x, int16_t y);
	void WriteVertical   (const String& sentence, int16_t x, int16_t y);
	void WriteVertical   (const WString& sentence, int16_t x, int16_t y);
	void Write		     (const String& sentence, int16_t x, int16_t y, int16_t width, int16_t height,
						  Align horizontal, Align vertical);
	void Write			 (const WString& sentence, int16_t x, int16_t y, int16_t width, int16_t height,
						  Align horizontal, Align vertical);
	void Write			 (const char c, int16_t x, int16_t y);
	void Write			 (const wchar_t c, int16_t x, int16_t y);
	void UpdateConsole	 ();

private:
	ConsoleBuffer* m_buffers;
	bool		   m_bufferIndex;

	void ClearBuffer();
};