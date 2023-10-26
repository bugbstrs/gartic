#include "User.h"

User::User() :
	m_username(std::string()),
	m_credits(0),
	m_isPlaying(false)
{}

User::User(const std::string& username, uint64_t credits, bool isPlaying) :
	m_username(username),
	m_credits(credits),
	m_isPlaying(isPlaying)
{}

void User::SetUsername(const std::string& username)
{
	m_username = username;
}

void User::SetCredits(int credits)
{
	m_credits = credits;
}

std::string User::GetUsername() const
{
	return std::string();
}


uint64_t User::GetCredits() const
{
	return m_credits;
}

bool User::IsPlaying() const
{
	return m_isPlaying;
}

void User::SetPlayingState(bool isPlaying)
{
	m_isPlaying = isPlaying;
}
