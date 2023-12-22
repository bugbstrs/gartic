#pragma once

#include <cstdint>
#include <string>

#include "Time.h"

namespace http
{
    class Player
    {
    public:
#pragma region Player
        Player()                                       noexcept;
        Player(const Player& otherPlayer)              noexcept;
        Player(Player&& otherPlayer)                   noexcept;
        Player(const std::string& username, uint16_t points = 0);

        ~Player() = default;
#pragma endregion constructors & destructor

#pragma region Player
        uint16_t GetPoints() const noexcept;
        const std::string& GetName() const noexcept;
        bool GetGuessed() const noexcept;
        Time GetTime() const noexcept;
#pragma endregion getters

#pragma region Player
        void SetPoints(uint16_t newPoints);
        void SetName(const std::string& newName);
        void SetTime(const Time& newTime);
        void SetGuessed(bool newGuessed);
#pragma endregion setters

#pragma region Player
        void AddPoints(uint16_t noOfPointsToBeAdded) noexcept;
#pragma endregion functionality

#pragma region Player
        bool    operator== (const Player& otherPlayer) const noexcept;
        Player& operator=  (const Player& otherPlayer) noexcept;
        Player& operator=  (Player&& otherPlayer)      noexcept;
#pragma endregion overloaded operators

    private:
        std::string m_user;

        Time m_active;

        uint16_t m_points;

        bool m_guessed;
    };
}