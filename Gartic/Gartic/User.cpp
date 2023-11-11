module User;

import <string>;
import <vector>;
import <algorithm>;

User::User():
	m_username{ String{} },
	m_credits{0},
	m_isPlaying{ false },
	m_averagePoints{0},
	m_matchesPoints{ Int16Vector{} }
{}

User::User(const String& username, uint64_t credits, bool isPlaying):
	m_username{ username },
	m_credits{ credits },
	m_isPlaying{ isPlaying },
	m_averagePoints{ 0 },
	m_matchesPoints{ Int16Vector{} }
{}

User::User(const User& otherUser) :
	m_username{ otherUser.m_username },
	m_credits{ otherUser.m_credits },
	m_isPlaying{ otherUser.m_isPlaying },
	m_averagePoints{ otherUser.m_averagePoints },
	m_matchesPoints{ otherUser.m_matchesPoints }
{}

void User::SetUsername(const String& username)
{
	m_username = username;
}

void User::SetCredits(int credits)
{
	m_credits = credits;
}

String User::GetUsername() const noexcept
{
	return m_username;
}

uint64_t User::GetCredits() const noexcept
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

User& User::operator=(const User& otherUser)
{
	if (this != &otherUser) {
		this->m_username = otherUser.m_username;
		this->m_averagePoints = otherUser.m_averagePoints;
		this->m_matchesPoints = otherUser.m_matchesPoints;
		this->m_credits = otherUser.m_credits;
		this->m_isPlaying = otherUser.m_isPlaying;
	}
	return *this;
}

bool User::operator==(const User& otherUser) const noexcept
{
	return this->m_username == otherUser.m_username && this->m_credits == otherUser.m_credits && this->m_averagePoints == otherUser.m_averagePoints && this->m_isPlaying == otherUser.m_isPlaying && std::equal(this->m_matchesPoints.begin(), this->m_matchesPoints.end(), otherUser.m_matchesPoints.begin());
}
