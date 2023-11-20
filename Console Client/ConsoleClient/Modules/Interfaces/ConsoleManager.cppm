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
	~ConsoleManager();

	// Setters
	void NewConsole(const LPCWSTR title, int16_t width, int16_t height);
	void SetTextColor(ColorType color);
	void SetBackgroundColor(ColorType color);
	void SetColor(ColorType background, ColorType text);
	void SetCursor(bool visible, COORD coord = { 0,0 });
	void SetCursor(bool visible, int16_t x, int16_t y);

	// Output related
	void WriteHorizontal(const String& sentence, int16_t x, int16_t y);
	void WriteVertical(const String& sentence, int16_t x, int16_t y);
	void UpdateConsole();

private:
	ConsoleBuffer* m_buffers;
	bool m_bufferIndex;

	void ClearBuffer();
};