export module Vocabulary;

#pragma region Vocabulary
import <string>;
import <tuple>;
import <vector>;
#pragma endregion imports

#pragma region Vocabulary
using String       = std::string;
using StringTuple  = std::tuple<std::string, std::string, std::string>;
using StringVector = std::vector<std::string>;
#pragma endregion using statements

export class Vocabulary
{
public:
	StringTuple FetchWords();

private:
	StringVector m_words;
};