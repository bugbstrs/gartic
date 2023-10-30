module User;

import <string>;
import <vector>;

User::User():
	m_username(std::string()),
	m_credits(0),
	m_isPlaying(false),
	averagePoints(0),
	m_matchesPoints(std::vector <uint16_t>())
{}

User::User(const std::string& username, uint64_t credits, bool isPlaying):
	m_username(username),
	m_credits(credits),
	m_isPlaying(isPlaying),
	averagePoints(0),
	m_matchesPoints(std::vector <uint16_t>())
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

void User::AddMatchPoints(uint16_t matchPoint)
{
	m_matchesPoints.emplace_back(matchPoint);
}