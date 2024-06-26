#pragma once

#include <string>
#include <unordered_set>

#include "GarticDatabase.h"
#include "RoundTypeEnum.h"
#include "GameStatusEnum.h"
#include "Player.h"

namespace http
{
	class Round
	{
	public:
		Round() = delete;
		Round(std::vector<std::shared_ptr<Player>>& newPlayers, std::string& wordToGuess,
			  GarticStorage& storage, std::shared_ptr<Time>& roundTime,
			  int numberOfWordsToChooseFrom, GameStatus& gameStatus, RoundType newType = RoundType::Normal);

		void NextDrawer();

		RoundType GetRoundType() const noexcept;
		int GetRoundNumber() const noexcept;
		const std::string& GetWordToDisplay(std::string username) const noexcept;
		std::vector<std::string> GetWordsToChooseFrom();
		std::shared_ptr<Player> GetDrawer() const noexcept;

		void SetRoundType(RoundType newRoundType);
		void SetWordToDisplay(const std::string& word);

		int GetPickWordRemainingDuration();
		bool PickAWord(const std::string& pickedWord);
		void PickARandomWord();

		void StopAllTimers();

		void ActivateRevealLetters();
		void RevealOneLetter();

	private:
		RoundType m_type;

		std::string m_wordToDisplay;

		std::shared_ptr<Time> m_wordToDisplayTimer;
		std::shared_ptr<Time> m_halfRoundTimer;
		std::shared_ptr<Time> m_pickWordTimer;

		std::shared_ptr<Player> m_drawer;

		int m_roundNumber;

		int m_numberOfWordsToChooseFrom;
		std::vector<std::string> m_wordsToChooseFrom;
		std::unordered_set<std::string> m_wordsPicked;

		std::vector<std::shared_ptr<Player>>& m_players;
		std::shared_ptr<Time>& m_roundTime;
		std::string& m_wordToGuess;

		GarticStorage& m_storage;

		GameStatus& m_gameStatus;
	};
}

