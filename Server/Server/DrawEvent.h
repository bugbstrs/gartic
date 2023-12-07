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

	private:
		CanvasPoints m_canvasPoints;

		int m_x;
		int m_y;

		Color m_color;

		int m_width;
	};
}

