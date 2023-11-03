module User;

import <string>;
import <vector>;
import <algorithm>;

User::User():
	m_username(String()),
	m_credits(0),
	m_isPlaying(false),
	m_averagePoints(0),
	m_matchesPoints(Int16Vector())
{}

User::User(const String& username, uint64_t credits, bool isPlaying):
	m_username(username),
	m_credits(credits),
	m_isPlaying(isPlaying),
	m_averagePoints(0),
	m_matchesPoints(Int16Vector())
{}

void User::SetUsername(const String& username)
{
	m_username = username;
}

void User::SetCredits(int credits)
{
	m_credits = credits;
}

String User::GetUsername() const
{
	return m_username;
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

bool User::operator==(const User& secondUser)
{
	return this->m_username == secondUser.m_username && this->m_credits == secondUser.m_credits && this->m_averagePoints == secondUser.m_averagePoints && this->m_isPlaying == secondUser.m_isPlaying && std::equal(this->m_matchesPoints.begin(), this->m_matchesPoints.end(), secondUser.m_matchesPoints.begin());
}
