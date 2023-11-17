#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(Storage& storage) : m_db(storage)
{
}

void DatabaseManager::PopulateWordsEntity()
{
	std::ifstream filename;
	filename.open("words.txt");

	WordVector words;

	std::string word;

	while (filename >> word)
	{
		words.push_back(word);
	}

	for (const auto& word : words)
	{
		m_db.insert(WordsEntity{ word });
	}

	filename.close();
}

void DatabaseManager::PopulateUsersEntity()
{
	std::ifstream filename;
	filename.open("users.txt");

	int gamesPlayed, points;
	std::string username, password;

	std::vector<UsersEntity> users;

	while (filename >> gamesPlayed >> points >> username >> password)
	{
		users.push_back(UsersEntity{ gamesPlayed, points, username, password });
	}

	for (const auto& user : users)
	{
		m_db.insert(user);
	}

	filename.close();
}

WordVector DatabaseManager::FetchAllWords()
{
	WordVector allWords;

	auto words = m_db.get_all<WordsEntity>();
	for (const auto& word : words)
	{
		allWords.push_back(word.GetName());
	}

	return allWords;
}

UserVector DatabaseManager::FetchAllUsers()
{
	UserVector allUsers;

	auto users = m_db.get_all<UsersEntity>();
	for (const auto& user : users)
	{
		allUsers.push_back(user);
	}

	return allUsers;
}

std::ostream& operator<<(std::ostream& out, const WordVector& words)
{
	out << "Words: ";

	for (const auto& word : words)
	{
		out << "name: " << word << std::endl;
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, const UserVector& users)
{
	out << "Users: ";

	for (const auto& user : users)
	{
		out << "id: " << user.GetId() << " username: " << user.GetUsername() << " password: " << user.GetPassword() << " points: " << user.GetPoints() << " games played: " << user.GetGamesPlayed() << std::endl;
	}

	return out;
}
