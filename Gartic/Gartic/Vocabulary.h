#pragma once
import <tuple>;
import <string>;
import <vector>;

class Vocabulary
{
public:
	std::tuple<std::string, std::string, std::string> fetchWords();
private:
	std::vector<std::string> m_words;
};

