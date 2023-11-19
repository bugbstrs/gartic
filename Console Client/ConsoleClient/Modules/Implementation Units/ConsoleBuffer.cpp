module ConsoleBuffer;

import <Windows.h>;

ConsoleBuffer::ConsoleBuffer(int16_t width, int16_t height):
    m_width          { width                         },
    m_height         { height                        },
    m_writeRect      { 0, 0, width, height           },
    m_charInfoBuffer { new CHAR_INFO[width * height] },
    m_bufferSize     { width, height                 }
{
    m_buffer = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleScreenBufferSize(m_buffer, m_bufferSize);
    SetConsoleWindowInfo(m_buffer, TRUE, &m_writeRect);
}

ConsoleBuffer::~ConsoleBuffer()
{
    delete[] m_charInfoBuffer;
}

void ConsoleBuffer::SetBackgroundColor(ColorType color)
{
    m_color %= 16;
    m_color += 16 * (int) color;
}

void ConsoleBuffer::SetColor(ColorType background, ColorType text)
{
    m_color = 16 * (int) background + (int) text;
}

void ConsoleBuffer::SetTextColor(ColorType color)
{
    m_color  = m_color / 16 * 16;
    m_color += (int) color;
}

void ConsoleBuffer::Clear()
{
    for (int16_t x = 0; x < m_width; ++x)
    {
        for (int16_t y = 0; y < m_height; ++y)
        {
            m_charInfoBuffer[x + y * m_width].Attributes     = (int) ColorType::Black;
            m_charInfoBuffer[x + y * m_width].Char.AsciiChar = ' ';
        }
    }
}

void ConsoleBuffer::Write(const String& sentence, int16_t x, int16_t y)
{
    for (int16_t i = 0; i < sentence.size(); ++i)
    {
        m_charInfoBuffer[(x + i) + y * m_width].Attributes     = m_color;
        m_charInfoBuffer[(x + i) + y * m_width].Char.AsciiChar = sentence[i];
    }
}