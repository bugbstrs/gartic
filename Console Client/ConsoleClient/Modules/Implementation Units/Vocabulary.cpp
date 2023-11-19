module Vocabulary;

import <array>;
import <tuple>;
import <string>;
import <vector>;

import FileHandler;

using StringArray = std::array<std::string, 3>;

StringTuple Vocabulary::FetchWords()
{
	StringArray words;
	FileHandler fileHandler;
	
	for (size_t i = 0; i < 3; i++)
	{
		String word = fileHandler.Read(FileType::Dictionary);
		
		while (std::find(m_words.begin(), m_words.end(), word) == m_words.end())
		{
			word = fileHandler.Read(FileType::Dictionary);
		}

		words[i] = word;
	}

	return { words[0], words[1], words[2] };
}