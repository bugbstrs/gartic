module HorizontalLayout;

import <string>;

using String = std::string;

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

HorizontalLayout::HorizontalLayout(Align align, ColorType backgroundColor, int16_t maxWidth,
								   int16_t maxHeight, ConsoleManager *cm, int space):
	GUIObject { align, backgroundColor, backgroundColor, maxWidth, maxHeight, cm },
	m_space	  { space															 }
{}

HorizontalLayout::~HorizontalLayout()
{
	for (auto obj : m_objects)
		delete obj;
}

void HorizontalLayout::Draw()
{
	SetColor();

	DrawBackground();

	DrawContents();
}

void HorizontalLayout::AddObjects(std::vector<GUIObject*> objects)
{
	for (auto obj : objects)
		AddObject(obj);
}

void HorizontalLayout::AddObject(GUIObject* object)
{
	if (object->GetHeight() > m_height || object->GetWidth() > m_width)
		return;

	int16_t rightPoint{ object->GetWidth() };
	if (!m_objects.empty())
		rightPoint = m_objects[m_objects.size() - 1]->GetWidth() +
					 object->GetWidth() - 1 + m_space;

	while (rightPoint > m_width)
	{
		m_objects.erase(m_objects.begin());
		SetObjectsPosition();

		rightPoint = m_objects[m_objects.size() - 1]->GetWidth() +
					 object->GetWidth() - 1 + m_space;
	}

	m_objects.push_back(object);
	SetObjectsPosition();
}

void HorizontalLayout::DrawContents()
{
	for (auto obj : m_objects)
		obj->Draw();
}

void HorizontalLayout::SetObjectsPosition()
{
	COORD pos{m_upLeftCorner};
	for (auto object : m_objects)
	{
		object->InitializeTransform(pos);
		pos.X += object->GetWidth();
	}
}
