#include "Player.h"

#include <cstdint>

using namespace http;

Player::Player() noexcept :
    m_user{ "" },
    m_points{ 0 },
    m_active{new Time(5000)}
{}

Player::Player(const Player& otherPlayer) noexcept :
    m_user{ otherPlayer.m_user },
    m_points{ otherPlayer.m_points },
    m_active{ otherPlayer.m_active }
{}

Player::Player(Player&& otherPlayer) noexcept :
    m_user{ std::move(otherPlayer.m_user) },
    m_points{ std::move(otherPlayer.m_points) },
    m_active{ std::move(otherPlayer.m_active) }
{}

Player::Player(const std::string& username, uint16_t points) :
    m_user{ username },
    m_points{ points },
    m_active{new Time(5000)}
{}

http::Player::~Player()
{
    delete m_active;
}

uint16_t Player::GetPoints() const noexcept
{
    return m_points;
}

const std::string& http::Player::GetName() const noexcept
{
    return m_user;
}

bool http::Player::GetGuessed() const noexcept
{
    return m_guessed;
}

Time http::Player::GetTime() const noexcept
{
    return m_active;
}

void http::Player::SetPoints(uint16_t newPoints)
{
    m_points = newPoints;
}

void http::Player::SetName(const std::string& newName)
{
    m_user = newName;
}

void http::Player::SetTime(const Time& newTime)
{
    m_active = newTime;
}

void http::Player::SetGuessed(bool newGuessed)
{
    m_guessed = newGuessed;
}

void Player::AddPoints(uint16_t noOfPointsToBeAdded) noexcept
{
    m_points += noOfPointsToBeAdded;
}

void http::Player::SetActive()
{
    m_active.Reset();
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