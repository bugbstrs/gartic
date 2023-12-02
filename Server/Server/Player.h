#pragma once

#include <cstdint>

#include "UsersEntity.h"

namespace http
{
    class Player
    {
    public:
#pragma region Player
        Player()                                       noexcept;
        Player(const Player& otherPlayer)              noexcept;
        Player(Player&& otherPlayer)                   noexcept;
        Player(const UsersEntity& user, uint16_t points = 0);

        ~Player() = default;
#pragma endregion constructors & destructor

#pragma region Player
        uint16_t GetPoints() const noexcept;
        std::string GetName() const noexcept;
#pragma endregion getters

#pragma region Player
        void AddPoints(uint16_t noOfPointsToBeAdded) noexcept;
#pragma endregion functionality

#pragma region Player
        bool    operator== (const Player& otherPlayer) const noexcept;
        Player& operator=  (const Player& otherPlayer) noexcept;
        Player& operator=  (Player&& otherPlayer)      noexcept;
#pragma endregion overloaded operators

    private:
        uint16_t m_points;
        UsersEntity m_user;
    };
}