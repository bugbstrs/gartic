#pragma once

enum class GameStatus
{
	Drawing,
	PickingWord,
	Waiting,
	SpecialRound
};

class GameStatusWrapper
{
public:
	static std::string ToString(GameStatus status) {
		if (status == GameStatus::Drawing)
		{
			return "Drawing";
		}
		else if (status == GameStatus::PickingWord)
		{
			return "PickingWord";
		}
		else if (status == GameStatus::Waiting)
		{
			return "Waiting";
		}
		else
		{
			return "Special Round";
		}
	}
};