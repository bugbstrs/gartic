export module Player;

import <cstdint>;

export import User;

export class Player
{
public:
	// Constructors
	Player() noexcept;
	Player(const User& user, uint16_t points = 0);
	Player(const Player& otherPlayer) noexcept;
	Player(Player&& otherPlayer) noexcept;
	~Player() = default;
	
	// Getters
	uint16_t GetPoints() const noexcept;

	// Functionality
	void AddPoints(uint16_t noOfPointsToBeAdded) noexcept;

	// Overloaded operators
	Player& operator=(const Player& otherPlayer) noexcept;
	Player& operator=(Player&& otherPlayer) noexcept;
	bool operator==(const Player& otherPlayer) const noexcept;

private:
	uint16_t m_points;

	User m_user;
};