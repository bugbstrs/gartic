export module Vocabulary;

import <tuple>;
import <string>;
import <vector>;

export class Vocabulary
{
public:
	std::tuple<std::string, std::string, std::string> fetchWords();
private:
	std::vector<std::string> m_words;
};