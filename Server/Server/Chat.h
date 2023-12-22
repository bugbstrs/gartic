#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Player.h"

using String = std::string;
using StringVector = std::vector<String>;
using ChatMap = std::unordered_map<String, StringVector>;

namespace http
{
	class Chat
	{
	public:
		Chat(const std::vector<Player*>& players);

		void VerifyMessage(const String& username, const String& message);
		void AddMessage(const String& username, const String& message);

		const StringVector& GetAndDeleteMessages(const String& username);

		const ChatMap& GetChat() const noexcept;

		bool IsCloseEnough(const std::string& currGuess);

	private:
		static inline double kTreshold = 0.8;

	private:
		ChatMap m_messages;

		String m_wordToGuess;
	};
}