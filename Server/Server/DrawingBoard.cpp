#include "DrawingBoard.h"

import GarticExceptions;

using namespace http;

http::DrawingBoard::DrawingBoard(const std::vector<std::shared_ptr<Player>>& players)
{
    for (const auto& player : players)
    {
        m_events[player->GetName()] = {};
    }
}

void http::DrawingBoard::Draw(const std::string& username, const std::shared_ptr<DrawEvent> currEvent)
{
	for (auto [currUsername, currEventVector] : m_events)
	{
		if (currUsername != username)
		{
			m_events[currUsername].push_back(currEvent);
		}
	}
}

const std::unordered_map<std::string, std::vector<std::shared_ptr<DrawEvent>>>& http::DrawingBoard::GetAllEvents() const noexcept
{
    return m_events;
}

const std::vector<std::shared_ptr<DrawEvent>>& http::DrawingBoard::GetAndDeleteEvents(const std::string& username)
{
	if (m_events.find(username) != m_events.end())
	{
		std::vector<std::shared_ptr<DrawEvent>> eventsToReturn = m_events[username];

		m_events[username].clear();

		return eventsToReturn;
	}

	throw GarticException<UserDoesntExistException>("Chat > GetMessages(const std::string&): The given username doesn't exist!");
}