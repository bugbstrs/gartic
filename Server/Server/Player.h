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
        Player(const std::string& username, int points = 0);

        ~Player();
#pragma endregion constructors & destructor

#pragma region Player
        int GetPoints() const noexcept;
        const std::string& GetName() const noexcept;
        bool GetGuessed() const noexcept;
        Time* GetTime() const noexcept;
        int GetTimeWhenGuessed() const noexcept;
#pragma endregion getters

#pragma region Player
        void SetPoints(int newPoints);
        void SetName(const std::string& newName);
        void SetTime(Time* newTime);
        void SetGuessed(bool newGuessed);
        void SetTimeWhenGuessed(int newTimeWhenGuessed);
#pragma endregion setters

#pragma region Player
        void AddPoints(int noOfPointsToBeAdded) noexcept;
#pragma endregion functionality

#pragma region Player
        void SetActive();

        bool    operator== (const Player& otherPlayer) const noexcept;
        Player& operator=  (const Player& otherPlayer) noexcept;
        Player& operator=  (Player&& otherPlayer)      noexcept;
#pragma endregion overloaded operators

    private:
        std::string m_user;

        Time* m_active;

        int m_points;

        bool m_guessed;

        int m_timeWhenGuessed;
    };
}