#pragma once

#include <string>

namespace http
{
	class Round
	{
	public:
        Round() = default;
		Round(int numberOfSubRounds, std::string&& wordToGuess);

		bool IsLastSubRound() const noexcept;

		void NextSubRound();

	private:
		int m_playerToDraw;

		int m_currSubRound;

		int m_numberOfSubRounds;

		std::string m_wordToGuess;

		bool m_isLastSubRound;
	};
}
