#include "Player.h"

#include <cstdint>;

using namespace http;

Player::Player() noexcept :
    m_username{ "" },
    m_points{ 0 }
{}

Player::Player(const Player& otherPlayer) noexcept :
    m_username{ otherPlayer.m_username },
    m_points{ otherPlayer.m_points }
{}

Player::Player(Player&& otherPlayer) noexcept :
    m_username{ std::move(otherPlayer.m_username) },
    m_points{ std::move(otherPlayer.m_points) }
{}

Player::Player(const std::string& username, uint16_t points) :
    m_username{ username },
    m_points{ points }
{}

uint16_t Player::GetPoints() const noexcept
{
    return m_points;
}

std::string http::Player::GetName() const noexcept
{
    return m_username;
}

Time http::Player::GetTime() const noexcept
{
    return m_active;
}

bool http::Player::GetGuessed() const noexcept
{
    return m_guessed;
}

void http::Player::SetPoints(uint16_t newPoints)
{
    m_points = newPoints;
}

void http::Player::SetName(const std::string& newName)
{
    m_username = newName;
}

void http::Player::SetTime(const Time& newTime)
{
    m_time = newTime;
}

void http::Player::SetGuessed(bool newGuessed)
{
    m_guessed = newGuessed;
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