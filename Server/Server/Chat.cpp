#include "Chat.h"

#include <format>
#include <regex>
#include <cctype>
#include <ranges>

import GarticExceptions;

using namespace http;

http::Chat::Chat(std::vector<std::shared_ptr<Player>>& players, std::string& wordToGuess, std::shared_ptr<Time> gameTime, GameStatus gameStatus, GarticStorage& storage) :
	m_players{ players },
	m_gameStatus{ gameStatus },
	m_wordToGuess{ wordToGuess },
	m_gameTime{ gameTime },
	m_storage{ storage }
{
	std::transform(m_wordToGuess.begin(), m_wordToGuess.end(), m_wordToGuess.begin(),
		[](unsigned char c) { return std::tolower(c); });

	for (const auto& player : players)
	{
		m_messages[player->GetName()] = {};
	}
}

void http::Chat::VerifyMessage(const std::string& username, const std::string& message)
{
	std::string messageCopy = message;

	std::transform(messageCopy.begin(), messageCopy.end(), messageCopy.begin(),
		[](unsigned char c) { return std::tolower(c); });

	if (IsCloseEnough(messageCopy))
	{
		if (GetPlayerByName(username)->GetGuessed())
		{
			m_messages[username].push_back("[Server]: You allready guessed the word!");
			return;
		}

		if (messageCopy == m_wordToGuess)
		{
			GetPlayerByName(username)->SetGuessed(true);
			GetPlayerByName(username)->SetTimeWhenGuessed((m_gameTime->GetDuration() - m_gameTime->GetRemainingTime()) / 1000);

			CalculatePoints(username);

			// Add guessed message to everyone
			for (auto& messages : m_messages)
				messages.second.push_back("[Server]: " + username + " guessed the word!");

			// Remove the default message for player and add a custme one
			m_messages[username].pop_back();
			m_messages[username].push_back("[Server]: You guessed the word!");

			int numberOfPlayersWhoGuessed{ 0 };
			for (const auto& player : m_players)
			{
				if (player->GetGuessed())
					++numberOfPlayersWhoGuessed;
			}
			if (numberOfPlayersWhoGuessed == m_players.size() - 1)
				m_gameTime->CallFunction();
		}
		else {
			m_messages[username].push_back("[Server]: You are close!");
		}
	}
	else
	{
		AddMessage(username, message);
	}
}

void http::Chat::AddMessage(const std::string& username, const std::string& message)
{
	std::string stars;

	std::vector<std::string> words = SplitIntoWords(message);

	for (std::string& word : words)
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
		if (m_storage.CheckBannedWord(word))
		{
			stars.append(message.size(), '*');
			break;
		}
	}

	for (auto [currUsername, currMessage] : m_messages)
	{
		if (currUsername != username)
		{
			if (stars.size())
			{
				m_messages[currUsername].push_back(std::format("{}: {}", username, stars));
			}
			else
			{
				m_messages[currUsername].push_back(std::format("{}: {}", username, message));
			}
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
	if (auto playerWhoGuessedIt = std::ranges::find_if(m_players, isPlayerWhoGuessed); playerWhoGuessedIt != m_players.end())
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
	if (auto it = std::ranges::find_if(m_players, getPlayerByName); it != m_players.end())
	{
		return *it;
	}

	return {};
}

const std::vector<std::string>& http::Chat::SplitIntoWords(const std::string& sentence)
{
	m_words.clear();
	std::regex wordRegex("\\b\\w+\\b"); 

	auto wordsBegin = std::sregex_iterator(sentence.begin(), sentence.end(), wordRegex);
	auto wordsEnd = std::sregex_iterator();

	for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
		std::smatch match = *i;
		std::string matchStr = match.str();
		m_words.push_back(matchStr);
	}

	return m_words;
}
