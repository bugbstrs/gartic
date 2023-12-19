module DrawingBoard;

DrawingBoard::DrawingBoard(COORD upLeftCorner,
			int16_t maxWidth, int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ upLeftCorner, Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)				  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)			  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
}

DrawingBoard::DrawingBoard(int16_t x, int16_t y,
			int16_t maxWidth, int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ x, y, Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)				  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)			  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
}

DrawingBoard::DrawingBoard(int16_t maxWidth,
			int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)				  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)			  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
}

void DrawingBoard::Draw()
{
	if (!m_active)
		return;

	DrawContents();
}

void DrawingBoard::CheckInput()
{
	
}

void DrawingBoard::CheckCursor()
{
	static COORD prevPoz{ -1,-1 };
	COORD cursorPos{ m_im->GetCurrentCursorPosition() };
	if (IsPointInside(cursorPos) &&
		m_im->GetClickHold() && m_selectable)
	{
		if (prevPoz.X != -1)
		{
			Canvas newCanvas{ m_canvases.top() };
			newCanvas.DrawLine(m_sectorHeight * (prevPoz.Y - m_upLeftCorner.Y) + m_sectorHeight / 2,
							  m_sectorWidth * (prevPoz.X - m_upLeftCorner.X) + m_sectorWidth / 2,
							  m_sectorHeight * (cursorPos.Y - m_upLeftCorner.Y) + m_sectorHeight / 2,
							  m_sectorWidth * (cursorPos.X - m_upLeftCorner.X) + m_sectorWidth / 2,
							  ColorType::Green, 6);
			m_canvases.emplace(newCanvas);
		}
		prevPoz = cursorPos;
		return;
	}
	prevPoz = { -1,-1 };
}

void DrawingBoard::DrawContents()
{
	for (int i{0}; i < m_canvases.top().GetHeight(); i += m_sectorHeight)
		for (int j{0}; j < m_canvases.top().GetWidth(); j += m_sectorWidth)
		{
			SetColor(m_canvases.top().GetSectorColor(j, i, m_sectorWidth, m_sectorHeight));
			m_cm->Write(' ', j / m_sectorWidth + m_upLeftCorner.X, i / m_sectorHeight + m_upLeftCorner.Y);
		}
}

void DrawingBoard::SetColor(ColorType color)
{
	m_cm->SetColor(color, color);
}
