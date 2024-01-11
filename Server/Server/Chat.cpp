#include "Chat.h"

#include <format>

import GarticExceptions;

using namespace http;

http::Chat::Chat(std::vector<std::shared_ptr<Player>>& players, std::string& wordToGuess, std::shared_ptr<Time> gameTime):
	m_players{ players },
	m_wordToGuess{ wordToGuess },
	m_gameTime{ gameTime }
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
			GetPlayerByName(username)->SetGuessed(true);
			GetPlayerByName(username)->SetTimeWhenGuessed(m_gameTime->GetRemainingTime() / 1000);
			
			CalculatePoints(username);

			m_messages[username].push_back(std::format("{} guessed the word!", username));
		}
		else {
			m_messages[username].push_back("You are close!");
		}
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

std::vector<std::string> http::Chat::GetAndDeleteMessages(const std::string& username)
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

void http::Chat::CalculatePoints(const std::string& username)
{
	std::shared_ptr<Player> playerWhoGuessed;
	
	auto isPlayerWhoGuessed = [&username](const std::shared_ptr<Player>& player) { return player->GetName() == username; };
	if (auto playerWhoGuessedIt = std::find_if(m_players.begin(), m_players.end(), isPlayerWhoGuessed); playerWhoGuessedIt != m_players.end())
	{
		int remainingTime{ m_gameTime->GetRemainingTime() / 1000 };
		int totalTime{ m_gameTime->GetDuration() / 1000 };

		if (remainingTime >= totalTime / 2)
		{
			(*playerWhoGuessedIt)->AddPoints(100);
		}
		else
		{
			(*playerWhoGuessedIt)->AddPoints((totalTime - remainingTime) * 50 / totalTime);
		}
	}
}

std::shared_ptr<Player> http::Chat::GetPlayerByName(const std::string& username)
{
	auto getPlayerByName = [&username](const std::shared_ptr<Player> player) { return player->GetName() == username; };
	if (auto it = std::find_if(m_players.begin(), m_players.end(), getPlayerByName); it != m_players.end())
	{
		return *it;
	}

	return {};
}
