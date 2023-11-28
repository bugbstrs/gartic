module HorizontalLayout;

HorizontalLayout::HorizontalLayout(COORD upLeftCorner, Align align, ColorType backgroundColor,
								   int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm,
								   int space) :
	GUIObject { upLeftCorner, align, backgroundColor, backgroundColor, maxWidth, maxHeight, cm },
	m_space	  { space																		   }
{}

HorizontalLayout::HorizontalLayout(int16_t x, int16_t y, Align align, ColorType backgroundColor,
								   int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm,
							       int space) :
	GUIObject { x, y, align, backgroundColor, backgroundColor, maxWidth, maxHeight, cm },
	m_space   { space																   }
{}

void HorizontalLayout::AddObject(GUIObject* object)
{
	COORD upLeft = m_upLeftCorner;
	COORD downRight = { upLeft.X + m_width, upLeft.Y + m_height };
	if (!m_objects.empty())
	{
		upLeft    = m_objects[m_objects.size() - 1]->GetUpLeftCorner();
		upLeft.X += m_space;
		downRight = m_objects[m_objects.size() - 1]->GetDownRightCorner();
	}
	upLeft.X += downRight.X;
	upLeft.Y += downRight.Y;
	while (downRight.X > m_upLeftCorner.X + m_width - 1 && !m_objects.empty())
	{
		m_objects.erase(m_objects.begin());
	}
	
	m_objects.push_back(object);
	
	object->InitializeTransform();
}
