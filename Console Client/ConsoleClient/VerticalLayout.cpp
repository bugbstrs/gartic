module VerticalLayout;

VerticalLayout::VerticalLayout(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
							   ColorType backgroundColor, int16_t maxWidth, int16_t maxHeight,
							   ConsoleManager* cm, int space) :
	GUIObject { upLeftCorner, horizontalAlign, verticalAlign, backgroundColor,
				backgroundColor, maxWidth, maxHeight, cm					  },
	m_space	  { space														  }
{}

VerticalLayout::VerticalLayout(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
							   ColorType backgroundColor, int16_t maxWidth, int16_t maxHeight,
							   ConsoleManager* cm, int space) :
	GUIObject { x, y, horizontalAlign, verticalAlign, backgroundColor,
				backgroundColor, maxWidth, maxHeight, cm			  },
	m_space   { space												  }
{}

VerticalLayout::VerticalLayout(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
							   int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm, int space):
	GUIObject { horizontalAlign, verticalAlign, backgroundColor,
				backgroundColor, maxWidth, maxHeight, cm		},
	m_space	  { space											}
{}

VerticalLayout::~VerticalLayout()
{
	for (auto obj : m_objects)
		delete obj;
}

void VerticalLayout::Draw()
{
	if (!m_active)
		return;

	SetColor();

	DrawBackground();

	DrawContents();
}

void VerticalLayout::AddObjects(std::vector<GUIObject*> objects)
{
	for (auto obj : objects)
		AddObject(obj);
}

void VerticalLayout::AddObject(GUIObject* object)
{
	if (object->GetHeight() > m_height || object->GetWidth() > m_width)
	{
		delete object;
		return;
	}

	int16_t length{ object->GetHeight() };

	for (auto it = m_objects.rbegin(); it != m_objects.rend();)
	{
		length += (*it)->GetHeight() + m_space;
		if (length > m_height)
		{
			if ((*m_objects.begin()) == (*it))
				length -= (*it)->GetHeight() + m_space;

			delete (*it);
			it = decltype(it)(m_objects.erase(std::next(it).base()));
		} else
		{
			++it;
		}
	}


	m_objects.push_back(object);
	SetObjectsPosition();
}

void VerticalLayout::Clear()
{
	for (auto obj : m_objects)
		delete obj;
}

void VerticalLayout::DrawContents()
{
	for (auto obj : m_objects)
		obj->Draw();
}

int16_t VerticalLayout::GetTotalWidth()
{
	int16_t total = 0;
	for (auto& obj : m_objects)
		total += obj->GetHeight();
	return total;
}

void VerticalLayout::SetObjectsPosition()
{
	COORD pos;

	switch (m_verticalAlign)
	{
	case Align::Up:
		pos.Y = m_upLeftCorner.Y;
		break;
	case Align::Center:
		pos.Y = m_upLeftCorner.Y + m_height / 2 - GetTotalWidth() / 2;
		break;
	case Align::Down:
		pos.Y = m_upLeftCorner.Y + m_height - GetTotalWidth();
		break;
	default:
		break;
	}

	for (const auto& object : m_objects)
	{
		switch (m_horizontalAlign)
		{
		case Align::Left:
			pos.X = m_upLeftCorner.X;
			break;
		case Align::Center:
			pos.X = m_upLeftCorner.X + m_width / 2 - object->GetWidth() / 2;
			break;
		case Align::Right:
			pos.X = m_upLeftCorner.X + m_width - object->GetWidth();
			break;
		default:
			break;
		}

		object->InitializeTransform(pos);
		pos.Y += object->GetHeight() + m_space;
	}
}
