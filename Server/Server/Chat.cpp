#include "Chat.h"

void http::Chat::AddMessage(const std::pair<std::string, std::string>& messages)
{
	m_messages.push_back(messages);
}

const std::vector<std::pair<std::string, std::string>>& http::Chat::GetChat() const noexcept
{
	return m_messages;
}
