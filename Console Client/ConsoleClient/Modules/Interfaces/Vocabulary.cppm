export module Vocabulary;

import <tuple>;
import <string>;
import <vector>;

using String = std::string;
using StringVector = std::vector<std::string>;
using StringTuple = std::tuple<std::string, std::string, std::string>;

export class Vocabulary
{
public:
	StringTuple FetchWords();

private:
	StringVector m_words;
};