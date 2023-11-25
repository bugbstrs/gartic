module HorizontalLayout;

HorizontalLayout::HorizontalLayout(COORD upLeftCorner, Align align, ColorType backgroundColor,
								   int16_t maxWidth, int16_t maxHeight, int space) :
	GUIObject { upLeftCorner, align, backgroundColor, backgroundColor, maxWidth, maxHeight },
	m_space	  { space																	   }
{}

HorizontalLayout::HorizontalLayout(int16_t x, int16_t y, Align align, ColorType backgroundColor,
								   int16_t maxWidth, int16_t maxHeight, int space) :
	GUIObject { x, y, align, backgroundColor, backgroundColor, maxWidth, maxHeight },
	m_space   { space															   }
{}

void HorizontalLayout::AddObject(GUIObject* object)
{
	m_objects.push_back(object);
}
