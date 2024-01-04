#pragma once

#include<string>

enum class LobbyStatus
{
	WaitingToStart,
	StartedGame
};

class LobbyStatusWrapper
{
public:
	static std::string ToString(LobbyStatus status) {
		if (status == LobbyStatus::WaitingToStart)
		{
			return "WaitingToStart";
		}
		else 		
		{
			return "StartedGame";
		}
	}
};