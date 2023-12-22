#pragma once

#include "ColorEnum.h"
#include "CanvasPointsEnum.h"

namespace http
{
	class DrawEvent
	{
	public:
		DrawEvent() = default;

		~DrawEvent() = default;

		CanvasPoints GetCanvasPoints() const noexcept;
		
		int GetX() const noexcept;
		int GetY() const noexcept;

		Color GetColor() const noexcept;

		int GetWidth() const noexcept;

		void SetX(int newX);
		void SetY(int newY);

		void SetColor(Color newColor);

		void SetWidth(int newWidth);

		bool operator==(const DrawEvent& e2) { return true; };
		DrawEvent& operator=(const DrawEvent& e2) { return *this; };

	private:
		CanvasPoints m_canvasPoints;

		int m_x;
		int m_y;

		Color m_color;

		int m_width;
	};
}

