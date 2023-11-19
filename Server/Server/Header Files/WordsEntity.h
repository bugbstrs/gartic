#pragma once
#include <string>

class WordsEntity
{
public:
	WordsEntity() = default;
	WordsEntity(const std::string& newName);

	~WordsEntity() = default;

	void SetName(const std::string& newName);
	void SetId(int newId);

	int GetId() const;
	std::string GetName() const;

private:
	int id;
	std::string name;
};
