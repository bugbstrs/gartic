#include "Chat.h"

#include <format>

http::Chat::Chat(const std::vector<Player*>& players): 
{
	for (auto player : players)
	{
		m_message[player->GetName()] = {};
	}
}

void http::Chat::AddMessage(const String& username, const String& message)
{
	for (auto [currUsername, currMessage] : m_messages)
	{
		if (currUsername != username)
		{
			m_messages[currUsername].push_back(std::format("{}: {}", username, message));
		}
	}
}

const StringVector& http::Chat::GetMessages(const String& username)
{
	if (m_messages.find(username) != m_messages.end())
	{
		StringVector messagesToReturn = m_messages[username];

		m_messages[username].clear();

		return messagesToReturn;
	}

	//throw GarticException<UserDoesntExistException>("Chat > GetMessages(const std::string&): The given username doesn't exist!");
}

const ChatMap& http::Chat::GetChat() const noexcept
{
	return m_messages;
}
