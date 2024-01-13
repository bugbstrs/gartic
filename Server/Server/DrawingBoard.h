#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "crow.h"
#include "Player.h"

namespace http
{
	class DrawingBoard
	{
	public:
		DrawingBoard(const std::vector<std::shared_ptr<Player>>& players);

		~DrawingBoard() = default;

		void Draw(const std::string& username, const std::string& currEvent);

		const std::unordered_map<std::string, std::vector<std::string>>& GetAllEvents() const noexcept;
		
		const std::vector<std::string> GetAndDeleteEvents(const std::string& username);

	private:
		std::unordered_map<std::string, std::vector<std::string>> m_events;
	};
}

