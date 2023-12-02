#pragma once

#include <string>

namespace http
{
	class Round
	{
	public:
		Round() = delete;
		Round(int numberOfRounds, std::string&& wordToGuess);

		void NextSubRound();

	private:
		int m_playerToDraw;

		int m_currSubRound;

		int m_numberOfRounds;

		std::string m_wordToGuess;

		bool m_isLastSubRound;
	};
}
