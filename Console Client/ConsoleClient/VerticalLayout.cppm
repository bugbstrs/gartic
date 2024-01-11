export module VerticalLayout;

import <vector>;

import GUIObject;

export class VerticalLayout : public GUIObject
{
public:
	// Constructors
	VerticalLayout(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, int space);
	VerticalLayout(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
		ColorType backgroundColor, int16_t maxWidth, int16_t maxHeight,
		ConsoleManager* cm, int space);
	VerticalLayout(Align horizontalAlign, Align verticalAlign, ColorType backgroundColor,
		int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, int space);

	// Destructor
	~VerticalLayout();

	void Draw() override;

	void AddObjects	(std::vector<GUIObject*> objects);
	void AddObject	(GUIObject* object);
	void Clear		();
	bool IsEmpty	();

private:
	std::vector<GUIObject*> m_objects;
	int						m_space;

	void DrawContents() override;
	int16_t GetTotalWidth();
	void SetObjectsPosition();
};