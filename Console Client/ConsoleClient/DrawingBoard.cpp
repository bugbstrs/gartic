module DrawingBoard;

DrawingBoard::DrawingBoard(COORD upLeftCorner,
			int16_t maxWidth, int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ upLeftCorner, Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_canvas		{ canvasWidth, canvasHeight, backgroungColor			  }
{

}

DrawingBoard::DrawingBoard(int16_t x, int16_t y,
			int16_t maxWidth, int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ x, y, Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_canvas		{ canvasWidth, canvasHeight, backgroungColor			  }
{

}

DrawingBoard::DrawingBoard(int16_t maxWidth,
			int16_t maxHeight,
			ColorType backgroungColor, ConsoleManager* cm,
			InputManager* im, SelectableObject*& selected,
			uint64_t canvasWidth, uint64_t canvasHeight) :
	SelectableObject{ Align::Center, Align::Center,
					  ColorType::Black, ColorType::Black, maxWidth, maxHeight,
					  ColorType::Black, ColorType::Black, cm, im, selected    },
	m_canvas		{ canvasWidth, canvasHeight, backgroungColor			  }
{

}

void DrawingBoard::Draw()
{

}

void DrawingBoard::CheckInput()
{
	
}

void DrawingBoard::CheckCursor()
{

}

void DrawingBoard::DrawContents()
{

}
