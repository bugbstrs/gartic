#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Player.h"

namespace http
{
	class Chat
	{
	public:
		Chat() = delete;
		Chat(std::vector<std::shared_ptr<Player>>& players, std::string& wordToGuess, std::shared_ptr<Time> gameTime);

		void VerifyMessage(const std::string& username, const std::string& message);
		void AddMessage(const std::string& username, const std::string& message);

		std::vector<std::string> GetAndDeleteMessages(const std::string& username);

		const std::unordered_map<std::string, std::vector<std::string>>& GetChat() const noexcept;

		bool IsCloseEnough(const std::string& currGuess);

	private:
		void CalculatePoints(const std::string& username);

		std::shared_ptr<Player> GetPlayerByName(const std::string& username);

	private:
		static inline double kTreshold = 0.8;

	private:
		std::vector<std::shared_ptr<Player>>& m_players;

		std::unordered_map<std::string, std::vector<std::string>> m_messages;

		std::string& m_wordToGuess;

		std::shared_ptr<Time> m_gameTime;
	};
}