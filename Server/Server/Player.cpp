#include "Player.h"

#include <cstdint>;

using namespace http;

Player::Player() noexcept :
    m_user{ UsersEntity{} },
    m_points{ 0 }
{}

Player::Player(const Player& otherPlayer) noexcept :
    m_user{ otherPlayer.m_user },
    m_points{ otherPlayer.m_points }
{}

Player::Player(Player&& otherPlayer) noexcept :
    m_user{ std::move(otherPlayer.m_user) },
    m_points{ std::move(otherPlayer.m_points) }
{}

Player::Player(const UsersEntity& user, uint16_t points) :
    m_user{ user },
    m_points{ points }
{}

uint16_t Player::GetPoints() const noexcept
{
    return m_points;
}

std::string http::Player::GetName() const noexcept
{
    return m_user.GetUsername();
}

void Player::AddPoints(uint16_t noOfPointsToBeAdded) noexcept
{
    m_points += noOfPointsToBeAdded;
}

bool Player::operator==(const Player& otherPlayer) const noexcept
{
    return m_points == otherPlayer.m_points && m_user == otherPlayer.m_user;
}

Player& Player::operator=(const Player& otherPlayer) noexcept
{
    if (this != &otherPlayer)
    {
        m_points = otherPlayer.m_points;
        m_user = otherPlayer.m_user;
    }

    return *this;
}

Player& Player::operator=(Player&& otherPlayer) noexcept
{
    if (this != &otherPlayer)
    {
        m_points = std::move(otherPlayer.m_points);
        m_user = std::move(otherPlayer.m_user);
    }

    return *this;
}