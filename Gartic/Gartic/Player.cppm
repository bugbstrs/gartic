export module Player;

import <cstdint>;

export import User;

export class Player
{
public:
	// Constructors
	Player();
	Player(const User& user, uint16_t points = 0);
	Player(const Player& secondPlayer);
	~Player() = default;
	
	// Getters
	uint16_t GetPoints() const noexcept;

	// Functionality
	void AddPoints(int noOfPointsToBeAdded) noexcept;

	// Overloaded operators
	Player& operator=(const Player& secondPlayer);
	bool operator==(const Player& secondPlayer) noexcept;

private:
	uint16_t m_points;

	User m_user;
};