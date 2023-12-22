#pragma once

#include <vector>
#include <string>

namespace http
{
	class Chat
	{
	public:
		Chat() = default;

		void AddMessage(const std::pair<std::string, std::string>& messages);

		const std::vector<std::pair<std::string, std::string>>& GetChat() const noexcept;

	private:
		std::vector<std::pair<std::string, std::string>> m_messages;
	};
}