#pragma once

#include <vector>
#include <string>
#include <unordered_map>

using String = std::string;
using StringVector = std::vector<String>;
using ChatMap = std::unordered_map<String, StringVector>;

namespace http
{
	class Chat
	{
	public:
		Chat() = default;

		void AddMessage(const String& username, const String& message);

		const StringVector& GetMessages(const String& username);

		const ChatMap& GetChat() const noexcept;

	private:
		ChatMap m_messages;
	};
}