module Player;

import <cstdint>;

Player::Player(): 
	m_user(User()), 
	m_points(0)
{}

Player::Player(const User& user): 
	m_user(user), 
	m_points(0)
{}

uint16_t Player::GetPoints() const
{
	return m_points;
}

void Player::AddPoints(int noOfPointsToBeAdded)
{
	m_points += noOfPointsToBeAdded;
}

bool Player::operator==(const Player& secondPlayer)
{
	return this->m_points == secondPlayer.m_points && this->m_user == secondPlayer.m_user;
}
