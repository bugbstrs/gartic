module Player;

import <cstdint>;

Player::Player(): 
	m_user{ User{} },
	m_points{ 0 }
{}

Player::Player(const User& user, uint16_t points) :
	m_user{ user },
	m_points{ points }
{}

Player::Player(const Player& secondPlayer) :
	m_user{ secondPlayer.m_user },
	m_points{ secondPlayer.m_points }
{}

uint16_t Player::GetPoints() const noexcept
{
	return m_points;
}

void Player::AddPoints(int noOfPointsToBeAdded) noexcept
{
	m_points += noOfPointsToBeAdded;
}

Player& Player::operator=(const Player& secondPlayer)
{
	if (this != &secondPlayer) {
		this->m_points = secondPlayer.m_points;
		this->m_user = secondPlayer.m_user;
	}
	return *this;
}

bool Player::operator==(const Player& secondPlayer) noexcept
{
	return this->m_points == secondPlayer.m_points && this->m_user == secondPlayer.m_user;
}
