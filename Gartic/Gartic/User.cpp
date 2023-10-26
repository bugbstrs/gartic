#include "User.h"

User::User()
{
	m_username = std::string();
	m_credits = 0;
	m_isPlaying = false;
}

User::User(const std::string& username, uint64_t credits, bool isPlaying) :
	m_username(username),
	m_credits(credits),
	m_isPlaying(isPlaying)
{}

std::string User::GetUsername() const
{
	return std::string();
}

void User::SetUsername(const std::string& username)
{
	m_username = username;
}
