#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace http
{
	class Chat
	{
	public:
		Chat() = default;

		void AddMessage(const std::string& username, const std::string& message);

		const std::unordered_map<std::string, std::vector<std::string>>& GetChat() const noexcept;

	private:
		std::unordered_map<std::string, std::vector<std::string>> m_messages;
	};
}