#pragma once
#include "User.h"

class Player
{
public:
	Player();
	Player(const User& user);
	uint16_t GetPoints() const;
	void AddPoints(int noOfPointsToBeAdded);
private:
	User m_user;
	uint16_t m_points;
};