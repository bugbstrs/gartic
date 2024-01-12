export module DrawingBoard;

import <stack>;
import <queue>;
import <vector>;
import <thread>;

import SelectableObject;
import Canvas;

using Color = ColorType;
using Threads = std::vector<std::thread>;

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

	enum class Option
	{
		draw,
		fill
	};

	class DrawEvent
	{
	public:

	private:
	};
	class StartDrawing : public DrawEvent
	{
	public:

	private:
		int x;
		int y;
		Color color;
		int width;
	};
	class KeepDrawing : public DrawEvent
	{
	public:

	private:
		int x;
		int y;
	};
	class Fill : public DrawEvent
	{
	public:

	private:
		int x;
		int y;
		Color color;
	};
	class Undo : public DrawEvent
	{
	public:

	private:
	};
	class Clear : public DrawEvent
	{
	public:

	private:
	};

	void Undo		 ();
	void Clear		 ();
	void SetOption	 (Option option);
	void SetPenWidth (int width);
	void SetDrawColor(Color color);

	void SendDrawEvent(DrawEvent drawEvent);
	const std::vector<DrawEvent>& GetDrawEvents();

	void FloodFill(COORD startingPoint, COORD pointToExecuteAt, Color startingColor, Color colorToBeFilledWith);
	void DrawStartingPixels(COORD startingPoint, COORD pointToExecuteAt, Color startingColor, Color colorToBeFilledWith, Threads& threads);
	void GenericFill(COORD startingPoint, COORD pointToExecuteAt, Color startingColor, Color colorToBeFilledWith);

	void Draw		 () override;
	void CheckInput	 () override;
	void CheckCursor () override;

private:
	std::stack<Canvas> m_canvases;
	Option			   m_option;
	Color			   m_color;
	int				   m_penWidth;
	int				   m_sectorWidth;
	int				   m_sectorHeight;

	void DrawContents() override;
	void SetColor	 (Color color);
};