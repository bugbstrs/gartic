#include "GameSettings.h"

http::GameSettings::GameSettings()
{
	std::ifstream filename;

	filename.open(kSettingsFile);

	if (!filename.eof())
	{
		filename >> m_roundsNumber;
	}

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
		filename >> m_wordCount;
	}
}

int http::GameSettings::GetDrawTime() const noexcept
{
	return m_drawTime;
}

int http::GameSettings::GetWordCount() const noexcept
{
	return m_wordCount;
}

void http::GameSettings::SetWordCount(int wordCount) noexcept
{
	m_wordCount = wordCount;
}

void http::GameSettings::SetRoundsNumber(int roundsNumber) noexcept
{
	m_roundsNumber = roundsNumber;
}

void http::GameSettings::SetDrawTime(int drawTime) noexcept
{
	m_drawTime = drawTime;
}

int http::GameSettings::GetRoundsNumber() const noexcept
{
	return m_roundsNumber;
}

int http::GameSettings::GetPlayersNumber() const noexcept
{
	return m_playersNumber;
}
