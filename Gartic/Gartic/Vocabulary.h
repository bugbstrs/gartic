#pragma once
#include <tuple>
#include <string>
#include <vector>

class Vocabulary
{
public:
	std::tuple<std::string, std::string, std::string> fetchWords();
private:
	std::vector<std::string> m_words;
};

