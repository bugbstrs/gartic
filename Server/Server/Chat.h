#pragma once

#include <vector>
#include <string>

namespace http
{
	class Chat
	{
	public:
		Chat();

		void AddMessage(const std::pair<std::string, std::string>& messages);

		std::vector<std::pair<std::string, std::string>> GetChat() const noexcept;

	private:
		std::vector<std::pair<std::string, std::string>> m_messages;
	};
}