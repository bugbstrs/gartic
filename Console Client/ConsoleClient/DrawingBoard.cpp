module DrawingBoard;

import <sstream>;

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
	m_penWidth		{ 4												  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
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
	m_penWidth		{ 4												  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
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
	m_penWidth		{ 4												  }
{
	m_canvases.emplace(canvasWidth, canvasHeight, backgroungColor);
}

void DrawingBoard::DrawLine(int x1, int y1, int x2, int y2)
{
	m_canvases.top().DrawLine(m_sectorWidth * (x1 - m_upLeftCorner.X) + m_sectorWidth / 2,
							  m_sectorHeight * (y1 - m_upLeftCorner.Y) + m_sectorHeight / 2,
							  m_sectorWidth * (x2 - m_upLeftCorner.X) + m_sectorWidth / 2,
							  m_sectorHeight * (y2 - m_upLeftCorner.Y) + m_sectorHeight / 2,
							  m_color, m_penWidth);
}

void DrawingBoard::Fill(int x, int y)
{
	// TODO: Fill
}

void DrawingBoard::Undo()
{
	if (m_selectable)
		m_drawEvents.push_back("undo");

	if (m_canvases.size() > 1)
		m_canvases.pop();
}

void DrawingBoard::Clear()
{
	if (m_selectable)
		m_drawEvents.push_back("clear");

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

void DrawingBoard::SendDrawEvent(const std::string& drawEvent)
{
	std::istringstream drawEventStream{ drawEvent };
	std::string string;
	drawEventStream >> string;
	static int prevX, prevY;
	if (string == "startDrawing")
	{
		int color;
		drawEventStream >> prevX >> prevY >> color >> m_penWidth;
		m_color = FromIntToConsoleColor(color);
		m_canvases.emplace(m_canvases.top());
	}
	else if (string == "keepDrawing")
	{
		int x, y;
		drawEventStream >> x >> y;
		DrawLine(prevX, prevY, x, y);
		prevX = x, prevY = y;
	}
	else if (string == "fill")
	{
		int x, y;
		int color;
		drawEventStream >> x >> y >> color;
		m_color = FromIntToConsoleColor(color);
		Fill(x, y);
	}
	else if (string == "undo")
	{
		Undo();
	}
	else if (string == "clear")
	{
		Clear();
	}
}

const std::vector<std::string> DrawingBoard::GetDrawEvents()
{
	std::vector<std::string> result{ m_drawEvents };
	m_drawEvents.clear();
	return result;
}

void DrawingBoard::FloodFill(COORD startingPoint, COORD pointToExecuteAt, Color startingColor, Color colorToBeFilledWith)
{
	Threads threads;
	DrawStartingPixels(startingPoint, pointToExecuteAt, startingColor, colorToBeFilledWith, threads);
	for (auto& thread : threads)
		thread.join();
}

void DrawingBoard::DrawStartingPixels(COORD startingPoint, COORD pointToExecuteAt, Color startingColor, Color colorToBeFilledWith, Threads& threads)
{
	if (m_canvases.top().GetPixelColor(pointToExecuteAt.X, pointToExecuteAt.Y) != startingColor ||
		m_canvases.top().GetPixelColor(pointToExecuteAt.X, pointToExecuteAt.Y) == colorToBeFilledWith)
		return;

	double distance = std::sqrt(std::pow(pointToExecuteAt.X - startingPoint.X, 2) + std::pow(pointToExecuteAt.Y - startingPoint.Y, 2));

	if (distance <= 25)
	{
		if (distance >= 24)
			threads.emplace_back(std::thread(&DrawingBoard::GenericFill, this, pointToExecuteAt, std::ref(pointToExecuteAt), startingColor, colorToBeFilledWith));
		else
			m_canvases.top().SetPixelColor(pointToExecuteAt.X, pointToExecuteAt.Y, colorToBeFilledWith);

		COORD executeAt{ pointToExecuteAt };
		++executeAt.X;
		DrawStartingPixels(startingPoint, executeAt, startingColor, colorToBeFilledWith, threads);
		executeAt = pointToExecuteAt;
		--executeAt.X;
		DrawStartingPixels(startingPoint, executeAt, startingColor, colorToBeFilledWith, threads);
		executeAt = pointToExecuteAt;
		++executeAt.Y;
		DrawStartingPixels(startingPoint, executeAt, startingColor, colorToBeFilledWith, threads);
		executeAt = pointToExecuteAt;
		--executeAt.Y;
		DrawStartingPixels(startingPoint, executeAt, startingColor, colorToBeFilledWith, threads);
	}
}

void DrawingBoard::GenericFill(COORD startingPoint, COORD pointToExecuteAt, Color startingColor, Color colorToBeFilledWith)
{
	if (m_canvases.top().GetPixelColor(pointToExecuteAt.X, pointToExecuteAt.Y) != startingColor)
		return;

	COORD currentPoint;
	std::queue<COORD> pointsQueue;
	pointsQueue.push(pointToExecuteAt);

	while (!pointsQueue.empty())
	{
		currentPoint = pointsQueue.front();
		pointsQueue.pop();

		if (m_canvases.top().GetPixelColor(currentPoint.X, currentPoint.Y) != startingColor ||
			m_canvases.top().GetPixelColor(currentPoint.X, currentPoint.Y) == colorToBeFilledWith)
			continue;

		m_canvases.top().SetPixelColor(currentPoint.X, currentPoint.Y, colorToBeFilledWith);

		pointsQueue.push(COORD{ currentPoint.X, short(currentPoint.Y + 1) });
		pointsQueue.push(COORD{ currentPoint.X, short(currentPoint.Y - 1) });
		pointsQueue.push(COORD{ short(currentPoint.X - 1), currentPoint.Y });
		pointsQueue.push(COORD{ short(currentPoint.X + 1), currentPoint.Y });
	}
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
	if (!m_selectable)
		return;
	static bool isWaitingToSave{ true };
	static COORD prevPos{ -1,-1 };
	COORD cursorPos{ m_im->GetCurrentCursorPosition() };
	if (IsPointInside(cursorPos))
	{
		if (m_im->GetClickPressed() && m_option == Option::fill)
		{
			std::string drawEvent{ "fill " };
			drawEvent += std::to_string(cursorPos.X);
			drawEvent += " ";
			drawEvent += std::to_string(cursorPos.Y);
			drawEvent += " ";
			drawEvent += std::to_string(FromConsoleColorToInt(m_color));
			m_drawEvents.push_back(drawEvent);
			Fill(cursorPos.X, cursorPos.Y);
			//m_canvases.emplace(m_canvases.top());
			//FloodFill({ short(m_sectorWidth * (cursorPos.X - m_upLeftCorner.X) + m_sectorWidth / 2) ,
			//			short(m_sectorHeight* (cursorPos.Y - m_upLeftCorner.Y) + m_sectorHeight / 2) },
			//		  { short(m_sectorWidth * (cursorPos.X - m_upLeftCorner.X) + m_sectorWidth / 2) ,
			//			short(m_sectorHeight * (cursorPos.Y - m_upLeftCorner.Y) + m_sectorHeight / 2) },
			//			m_canvases.top().GetPixelColor(short(m_sectorWidth * (cursorPos.X - m_upLeftCorner.X) + m_sectorWidth / 2),
			//								short(m_sectorHeight * (cursorPos.Y - m_upLeftCorner.Y) + m_sectorHeight / 2)), m_color);
		}else
		if (m_im->GetClickHold() && m_option == Option::draw)
		{
			if (prevPos.X != -1)
			{
				if (isWaitingToSave)
				{
					isWaitingToSave = false;
					m_canvases.emplace(m_canvases.top());

					std::string drawEvent{ "startDrawing " };
					drawEvent += std::to_string(prevPos.X);
					drawEvent += " ";
					drawEvent += std::to_string(prevPos.Y);
					drawEvent += " ";
					drawEvent += std::to_string(FromConsoleColorToInt(m_color));
					drawEvent += " ";
					drawEvent += std::to_string(m_penWidth);
					m_drawEvents.push_back(drawEvent);
				}
				std::string drawEvent{ "keepDrawing " };
				drawEvent += std::to_string(cursorPos.X);
				drawEvent += " ";
				drawEvent += std::to_string(cursorPos.Y);
				m_drawEvents.push_back(drawEvent);
				DrawLine(prevPos.X, prevPos.Y, cursorPos.X, cursorPos.Y);
			}
			prevPos = cursorPos;
			return;
		}
	}
	
	if (prevPos.X != -1)
		isWaitingToSave = true;

	prevPos = { -1,-1 };
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
