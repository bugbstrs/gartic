#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "DrawEvent.h"
#include "Player.h"

namespace http
{
	class DrawingBoard
	{
	public:
		DrawingBoard(const std::vector<std::shared_ptr<Player>>& players);

		~DrawingBoard() = default;

		void Draw(const std::string& username, std::shared_ptr<DrawEvent> currEvent);

		const std::unordered_map<std::string, std::vector<std::shared_ptr<DrawEvent>>>& GetAllEvents() const noexcept;
		
		const std::vector<std::shared_ptr<DrawEvent>>& GetAndDeleteEvents(const std::string& username);

	private:
		std::unordered_map<std::string, std::vector<std::shared_ptr<DrawEvent>>> m_events;
	};
}

