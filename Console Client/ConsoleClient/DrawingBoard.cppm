export module DrawingBoard;

import SelectableObject;
import Canvas;

export class DrawingBoard : public SelectableObject
{
public:
	DrawingBoard(COORD upLeftCorner, int16_t maxWidth, int16_t maxHeight,
				 ColorType backgroungColor, ConsoleManager* cm,
				 InputManager* im, SelectableObject*& selected);
	DrawingBoard(int16_t x, int16_t y, int16_t maxWidth, int16_t maxHeight,
				 ColorType backgroungColor, ConsoleManager* cm,
				 InputManager* im, SelectableObject*& selected);
	DrawingBoard(int16_t maxWidth, int16_t maxHeight,
				 ColorType backgroungColor, ConsoleManager* cm,
				 InputManager* im, SelectableObject*& selected);

	~DrawingBoard() = default;

	void Draw		() override;
	void CheckInput	() override;
	void CheckCursor() override;

private:
	Canvas m_canvas;

	void DrawContents() override;
};