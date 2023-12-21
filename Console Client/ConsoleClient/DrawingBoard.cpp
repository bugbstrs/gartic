module DrawingBoard;

DrawingBoard::DrawingBoard(COORD upLeftCorner,
			int16_t maxWidth, int16_t maxHeight,
						   Color backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ upLeftCorner, Align::Center, Align::Center,
					  Color::Black, Color::Black, maxWidth, maxHeight,
					  Color::Black, Color::Black, cm, im, selected    },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)		  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)	  },
	m_option		{ Option::draw									  },
	m_color			{ Color::Black									  },
	m_penWidth		{ 6												  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
	m_selectable = false;
}

DrawingBoard::DrawingBoard(int16_t x, int16_t y,
			int16_t maxWidth, int16_t maxHeight,
			Color backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ x, y, Align::Center, Align::Center,
					  Color::Black, Color::Black, maxWidth, maxHeight,
					  Color::Black, Color::Black, cm, im, selected    },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)		  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)	  },
	m_option		{ Option::draw									  },
	m_color			{ Color::Black									  },
	m_penWidth		{ 6												  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
	m_selectable = false;
}

DrawingBoard::DrawingBoard(int16_t maxWidth,
			int16_t maxHeight,
			Color backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ Align::Center, Align::Center,
					  Color::Black, Color::Black, maxWidth, maxHeight,
					  Color::Black, Color::Black, cm, im, selected    },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)		  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)	  },
	m_option		{ Option::draw									  },
	m_color			{ Color::Black									  },
	m_penWidth		{ 6												  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
	m_selectable = false;
}

void DrawingBoard::Undo()
{
	if (m_canvases.size() > 1)
		m_canvases.pop();
}

void DrawingBoard::Clear()
{
	while (m_canvases.size() > 1)
		m_canvases.pop();
}

void DrawingBoard::SetOption(Option option)
{
	m_option = option;
}

void DrawingBoard::SetPenWidth(int width)
{
	m_penWidth = width;
}

void DrawingBoard::SetDrawColor(Color color)
{
	m_color = color;
}

void DrawingBoard::Draw()
{
	if (!m_active)
		return;

	DrawContents();
}

void DrawingBoard::CheckInput(){} // Needs to be overrided

void DrawingBoard::CheckCursor()
{
	static bool isWaitingToSave{ true };
	static COORD prevPoz{ -1,-1 };
	COORD cursorPos{ m_im->GetCurrentCursorPosition() };
	if (IsPointInside(cursorPos))
	{
		if (m_im->GetClickPressed() && m_option == Option::fill)
		{
			//fill
		}
		if (m_im->GetClickHold() && m_option == Option::draw)
		{
			if (prevPoz.X != -1)
			{
				if (isWaitingToSave)
				{
					isWaitingToSave = false;
					m_canvases.emplace(m_canvases.top());
				}
				m_canvases.top().DrawLine(m_sectorWidth * (prevPoz.X - m_upLeftCorner.X) + m_sectorWidth / 2,
										  m_sectorHeight * (prevPoz.Y - m_upLeftCorner.Y) + m_sectorHeight / 2,
										  m_sectorWidth * (cursorPos.X - m_upLeftCorner.X) + m_sectorWidth / 2,
										  m_sectorHeight * (cursorPos.Y - m_upLeftCorner.Y) + m_sectorHeight / 2,
										  m_color, m_penWidth);
			}
			prevPoz = cursorPos;
			return;
		}
	}
	
	if (prevPoz.X != -1)
		isWaitingToSave = true;

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

void DrawingBoard::SetColor(Color color)
{
	m_cm->SetColor(color, color);
}
