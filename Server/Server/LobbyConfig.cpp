#include "LobbyConfig.h"

http::LobbyConfig::LobbyConfig()
{
	std::ifstream filename;

	filename.open(kConfigFile);

	if (!filename.eof())
	{
		filename >> m_playersNumber;
	}

	if (!filename.eof())
	{
		filename >> m_drawTime;
	}

	if (!filename.eof())
	{
		filename >> m_roundsNumber;
	}
}

int http::LobbyConfig::GetPlayersNumber() const noexcept
{
	return m_playersNumber;
}

int http::LobbyConfig::GetDrawTime() const noexcept
{
	return m_drawTime;
}

int http::LobbyConfig::GetRoundsNumber() const noexcept
{
	return m_roundsNumber;
}
