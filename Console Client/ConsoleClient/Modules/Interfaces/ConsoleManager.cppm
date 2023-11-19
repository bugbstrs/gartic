export module ConsoleManager;

export import ColorType;
import ConsoleBuffer;

using String = std::string;

export class ConsoleManager
{
public:
	// Constructors
	ConsoleManager();

	// Destructor
	~ConsoleManager() = default;

	// Setters
	void NewConsole(const LPCWSTR title, uint16_t width, uint16_t height);
	void SetConsoleScale(uint16_t x, uint16_t y);
	void SetCursor(uint16_t x, uint16_t y);
	void SetCursor(COORD coord);
	void SetBackgroundColor(ColorType color);
	void SetTextColor(ColorType color);
	void SetColor(ColorType background, ColorType text);
	
	// Output related
	void ClearScreen();
	void WriteVertical(const String& sentence, uint16_t x, uint16_t y);
	void WriteHorizontal(const String& sentence, uint16_t x, uint16_t y);

private:
	HANDLE m_h;
	uint16_t m_color;
};