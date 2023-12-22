#include "Chat.h"

void http::Chat::AddMessage(const std::string& username, const std::string& message)
{
	m_messages[username].push_back(message);
}

const std::unordered_map<std::string, std::vector<std::string>>& http::Chat::GetChat() const noexcept
{
	return m_messages;
}
