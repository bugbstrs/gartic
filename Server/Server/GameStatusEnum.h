#pragma once

enum class GameStatus
{
	PickingWord,
	Drawing,
	Finished
};

class GameStatusWrapper
{
public:
	static std::string ToString(GameStatus status) {
		if (status == GameStatus::PickingWord)
		{
			return "PickingWord";
		}
		else if (status == GameStatus::Drawing)
		{
			return "Drawing";
		}
		else if (status == GameStatus::Finished)
		{
			return "Finished";
		}
	}
};