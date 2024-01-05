#include "Chat.h"

#include <format>

import GarticExceptions;

using namespace http;

http::Chat::Chat(const std::vector<std::shared_ptr<Player>>& players)
{
	for (const auto& player : players)
	{
		m_messages[player->GetName()] = {};
	}
}

void http::Chat::VerifyMessage(const std::string& username, const std::string& message)
{
	if (IsCloseEnough(message))
	{
		if (message == m_wordToGuess)
		{
			m_messages[username].push_back("You guessed the word!");
		}
		
		m_messages[username].push_back("You are close!");
	}
	else
	{
		AddMessage(username, message);
	}
}

void http::Chat::AddMessage(const std::string& username, const std::string& message)
{
	for (auto [currUsername, currMessage] : m_messages)
	{
		if (currUsername != username)
		{
			m_messages[currUsername].push_back(std::format("{}: {}", username, message));
		}
	}
}

const std::vector<std::string>& http::Chat::GetAndDeleteMessages(const std::string& username)
{
	if (m_messages.find(username) != m_messages.end())
	{
		std::vector<std::string> messagesToReturn = m_messages[username];

		m_messages[username].clear();

		return messagesToReturn;
	}

	throw GarticException<UserDoesntExistException>("Chat > GetMessages(const std::string&): The given username doesn't exist!");
}

const std::unordered_map<std::string, std::vector<std::string>>& http::Chat::GetChat() const noexcept
{
	return m_messages;
}

bool http::Chat::IsCloseEnough(const std::string& currGuess)
{
	auto tokenize = [](const std::string& str, std::unordered_map<std::string, int>& wordFrequency) {
		size_t start = 0, end = 0;
		while ((end = str.find(' ', start)) != std::string::npos) {
			std::string word = str.substr(start, end - start);
			wordFrequency[word]++;
			start = end + 1;
		}
		std::string lastWord = str.substr(start);
		wordFrequency[lastWord]++;
		};

	std::unordered_map<std::string, int> freq1, freq2;
	tokenize(m_wordToGuess, freq1);
	tokenize(currGuess, freq2);

	double dotProduct = 0.0;
	for (const auto& entry : freq1)
	{
		dotProduct += entry.second * freq2[entry.first];
	}

	double mag1 = 0.0, mag2 = 0.0;
	for (const auto& entry : freq1)
	{
		mag1 += std::pow(entry.second, 2);
	}

	for (const auto& entry : freq2)
	{
		mag2 += std::pow(entry.second, 2);
	}

	double similarity = dotProduct / (std::sqrt(mag1) * std::sqrt(mag2));

	return similarity >= Chat::kTreshold;
}
