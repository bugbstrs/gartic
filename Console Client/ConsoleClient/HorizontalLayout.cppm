export module HorizontalLayout;

import <vector>;

import GUIObject;

export class HorizontalLayout : public GUIObject
{
public:
	// Constructors
	HorizontalLayout(COORD upLeftCorner, Align align, ColorType backgroundColor,
					 int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, int space);
	HorizontalLayout(int16_t x, int16_t y, Align align, ColorType backgroundColor,
					 int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm, int space);
	HorizontalLayout(Align align, ColorType backgroundColor, int16_t maxWidth,
					 int16_t maxHeight, ConsoleManager *cm, int space);

	// Destructor
	~HorizontalLayout();

	void Draw() override;

	void AddObjects (std::vector<GUIObject*> objects);
	void AddObject	(GUIObject* object);

private:
	std::vector<GUIObject*> m_objects;
	int						m_space;

	void DrawContents		() override;
	void SetObjectsPosition	();
};