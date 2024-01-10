#pragma once

#include <string>
#include <unordered_set>

#include "GarticDatabase.h"
#include "RoundTypeEnum.h"
#include "Player.h"

namespace http
{
	class Round
	{
	public:
		Round() = delete;
		Round(std::vector<std::shared_ptr<Player>>& newPlayers, std::string& wordToGuess,
			  GarticStorage& storage, int roundTime, int numberOfWordsToChooseFrom,
			  RoundType newType = RoundType::Normal);

		void NextDrawer();

		RoundType GetRoundType() const noexcept;
		int GetRoundNumber() const noexcept;
		const std::string& GetWordToDisplay() const noexcept;
		std::vector<std::string> GetWordsToChooseFrom();
		std::shared_ptr<Player> GetDrawer() const noexcept;

		void SetRoundType(RoundType newRoundType);
		void SetWordToDisplay(const std::string& word);

		int GetPickWordRemainingDuration();
		bool PickAWord(const std::string& pickedWord);
		void PickARandomWord();

		void ActivateRevealLetters();
		void RevealOneLetter();

	private:
		RoundType m_type;

		std::string m_wordToDisplay;

		Time* m_wordToDisplayTimer;
		Time* m_halfRoundTimer;
		Time* m_pickWordTimer;

		std::shared_ptr<Player> m_drawer;

		int m_roundNumber;

		int m_numberOfWordsToChooseFrom;
		std::vector<std::string> m_wordsToChooseFrom;
		std::unordered_set<std::string> m_wordsPicked;

		std::vector<std::shared_ptr<Player>>& m_players;
		std::string& m_wordToGuess;

		GarticStorage& m_storage;
	};
}

