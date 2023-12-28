#pragma once
#include "DrawEvent.h"

namespace http
{
	class StartDraw : public DrawEvent
	{
	public:
		StartDraw(int newX, int newY, int newWidth, int newColor);

		// Inherited via DrawEvent
		const std::string& Serialize() override;

		void Deserialize(const std::string&) override;

	private:
		int m_x;
		int m_y;
		int m_width;
		int m_color;

	};
}

