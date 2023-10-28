#include "Vocabulary.h"
#include "FileHandler.h"

import <array>;
import <tuple>;
import <string>;

std::tuple<std::string, std::string, std::string> Vocabulary::fetchWords()
{
	std::array<std::string, 3> words;
	
	for (int i = 0; i < 3; i++)
	{
		std::string word = FileHandler::read(FileHandler::FileType::Dictionary);
		
		while (std::find(m_words.begin(), m_words.end(), word) == m_words.end())
		{
			word = FileHandler::read(FileHandler::FileType::Dictionary);
		}

		words[i] = word;
	}

	return { words[0], words[1], words[2] };
}
