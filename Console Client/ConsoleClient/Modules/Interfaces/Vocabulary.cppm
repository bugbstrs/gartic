export module Vocabulary;

#pragma region Vocabulary
import <tuple>;
import <string>;
import <vector>;
#pragma endregion imports

#pragma region Vocabulary
using String = std::string;
using StringVector = std::vector<std::string>;
using StringTuple = std::tuple<std::string, std::string, std::string>;
#pragma endregion using statements

export class Vocabulary
{
public:
	StringTuple FetchWords();

private:
	StringVector m_words;
};