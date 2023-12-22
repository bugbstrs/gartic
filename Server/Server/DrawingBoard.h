#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "DrawEvent.h"

namespace http
{
	class DrawingBoard
	{
	public:
		DrawingBoard() = default;

		~DrawingBoard() = default;

		const std::unordered_map<std::string, std::vector<DrawEvent>>& GetEvents() const noexcept;

		void Fill(int x, int y, Color color);

		void Draw(int x, int y, Color color, int width);

	private:
		std::unordered_map<std::string, std::vector<DrawEvent>> m_events;
	};
}

