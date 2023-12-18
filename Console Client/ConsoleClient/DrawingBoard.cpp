module DrawingBoard;

DrawingBoard::DrawingBoard(COORD upLeftCorner,
			int16_t maxWidth, int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ upLeftCorner, Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_canvas		{ canvasWidth, canvasHeight, backgroungColor			  },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)				  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)			  }
{}

DrawingBoard::DrawingBoard(int16_t x, int16_t y,
			int16_t maxWidth, int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ x, y, Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_canvas		{ canvasWidth, canvasHeight, backgroungColor			  },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)				  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)			  }
{}

DrawingBoard::DrawingBoard(int16_t maxWidth,
			int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_canvas		{ canvasWidth, canvasHeight, backgroungColor			  },
	m_sectorWidth	{ static_cast<int>(canvasWidth / maxWidth)				  },
	m_sectorHeight	{ static_cast<int>(canvasHeight / maxHeight)			  }
{}

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

}

void DrawingBoard::DrawContents()
{
	for (int i{ 0 }; i < m_canvas.GetHeight(); i += m_sectorHeight)
		for (int j{ 0 }; j < m_canvas.GetWidth(); j += m_sectorWidth)
		{
			SetColor(m_canvas.GetSectorColor(j, i, m_sectorWidth, m_sectorHeight));
			m_cm->Write(' ', j / m_sectorWidth, i / m_sectorHeight);
		}
}

void DrawingBoard::SetColor(ColorType color)
{
	m_cm->SetColor(color, color);
}