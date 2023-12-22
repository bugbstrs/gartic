#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "DrawEvent.h"
#include "Player.h"

namespace http
{
	class DrawingBoard
	{
	public:
		DrawingBoard(const std::vector<Player*>& players);

		~DrawingBoard() = default;

		void Draw(const std::string& username, const DrawEvent& currEvent);

		const std::unordered_map<std::string, std::vector<DrawEvent>>& GetAllEvents() const noexcept;
		
		const std::vector<DrawEvent>& GetAndDeleteEvents(const std::string& username);

	private:
		std::unordered_map<std::string, std::vector<DrawEvent>> m_events;
	};
}

