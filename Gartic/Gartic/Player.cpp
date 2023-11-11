module Player;

import <cstdint>;

Player::Player() noexcept: 
	m_user{ User{} },
	m_points{ 0 }
{}

Player::Player(const User& user, uint16_t points) :
	m_user{ user },
	m_points{ points }
{}

Player::Player(const Player& otherPlayer) noexcept:
	m_user{ otherPlayer.m_user },
	m_points{ otherPlayer.m_points }
{}

Player::Player(Player&& otherPlayer) noexcept:
	m_user{ std::move(otherPlayer.m_user) },
	m_points{ std::move(otherPlayer.m_points) }
{}

uint16_t Player::GetPoints() const noexcept
{
	return m_points;
}

void Player::AddPoints(uint16_t noOfPointsToBeAdded) noexcept
{
	m_points += noOfPointsToBeAdded;
}

Player& Player::operator=(const Player& otherPlayer) noexcept
{
	if (this != &otherPlayer) {
		this->m_points = otherPlayer.m_points;
		this->m_user = otherPlayer.m_user;
	}
	return *this;
}

Player& Player::operator=(Player&& otherPlayer) noexcept
{
	if (this != &otherPlayer) {
		this->m_points = std::move(otherPlayer.m_points);
		this->m_user = std::move(otherPlayer.m_user);
	}
	return *this;
}

bool Player::operator==(const Player& otherPlayer) const noexcept
{
	return this->m_points == otherPlayer.m_points && this->m_user == otherPlayer.m_user;
}
