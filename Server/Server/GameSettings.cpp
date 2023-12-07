#include "GameSettings.h"

http::GameSettings::GameSettings()
{
	std::ifstream filename;

	filename.open(kSettingsFile);

	if (!filename.eof())
	{
		filename >> m_customRounds;
	}

	if (!filename.eof())
	{
		filename >> m_roundsNumber;
	}

	if (!filename.eof())
	{
		filename >> m_customRoundChance;
	}

	if (!filename.eof())
	{
		filename >> m_playersNumber;
	}

	if (!filename.eof())
	{
		filename >> m_drawTime;
	}
}

float http::GameSettings::GetDrawTime() const noexcept
{
	return m_drawTime;
}

int http::GameSettings::GetRoundsNumber() const noexcept
{
	return m_roundsNumber;
}

bool http::GameSettings::GetCustomRounds() const noexcept
{
	return m_customRounds;
}

int http::GameSettings::GetCustomRoundChance() const noexcept
{
	return m_customRoundChance;
}

int http::GameSettings::GetPlayersNumber() const noexcept
{
	return m_playersNumber;
}
