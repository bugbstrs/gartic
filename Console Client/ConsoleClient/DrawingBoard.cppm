export module DrawingBoard;

import <stack>;

import SelectableObject;
import Canvas;

using Color = ColorType;

export class DrawingBoard : public SelectableObject
{
public:
	DrawingBoard(COORD upLeftCorner, int16_t maxWidth, int16_t maxHeight,
				 Color backgroungColor, ConsoleManager* cm,
				 InputManager* im, SelectableObject*& selected,
				 uint64_t canvasWidth, uint64_t canvasHeight);
	DrawingBoard(int16_t x, int16_t y, int16_t maxWidth, int16_t maxHeight,
				 Color backgroungColor, ConsoleManager* cm,
				 InputManager* im, SelectableObject*& selected,
				 uint64_t canvasWidth, uint64_t canvasHeight);
	DrawingBoard(int16_t maxWidth, int16_t maxHeight,
				 Color backgroungColor, ConsoleManager* cm,
				 InputManager* im, SelectableObject*& selected,
				 uint64_t canvasWidth, uint64_t canvasHeight);

	~DrawingBoard() = default;

	void Undo		();
	void Clear		();
	bool &GetOption ();
	void Draw		() override;
	void CheckInput	() override;
	void CheckCursor() override;

private:
	std::stack<Canvas> m_canvases;
	Color			   m_color;
	bool			   m_option;// false = pen | true = fill
	int				   m_sectorWidth;
	int				   m_sectorHeight;

	void DrawContents() override;
	void SetColor	 (Color color);
};