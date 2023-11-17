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

struct User {
	int id = 0;
	std::string name;
};

bool DatabaseManager::CheckCredentials(const String& givenUsername, const String& givenPassword) const
{
	auto result1 = m_db.select(sqlite_orm::columns(&UsersEntity::GetId, &UsersEntity::GetUsername),
		sqlite_orm::where(sqlite_orm::is_equal(&UsersEntity::GetUsername, givenUsername)));

	auto result2 = m_db.select(sqlite_orm::columns(&UsersEntity::GetId, &UsersEntity::GetUsername), sqlite_orm::where(sqlite_orm::is_equal(&UsersEntity::GetPassword, givenPassword)));

	return !result1.empty() && !result2.empty();
}

bool DatabaseManager::CheckUsernameAlreadyExists(const String& givenUsername) const
{
	auto result = m_db.select(sqlite_orm::columns(&UsersEntity::GetId, &UsersEntity::GetUsername),
		sqlite_orm::where(sqlite_orm::is_equal(&UsersEntity::GetUsername, givenUsername)));

	return !result.empty();
}

void DatabaseManager::CreateUser(const String& givenUsername, const String& givenPassword) const
{
	if (CheckUsernameAlreadyExists(givenUsername))
	{
		return;		// possible exception to throw here
	}

	m_db.insert(UsersEntity{0, 0, givenUsername, givenPassword});
}

String DatabaseManager::FetchWord()
{
	int randomId = GenerateRandomId();

	auto result = m_db.select(sqlite_orm::columns(&WordsEntity::GetName),
		sqlite_orm::where(sqlite_orm::is_equal(&WordsEntity::GetId, randomId)));

	if (!result.empty())
	{
		return std::get<0>(result[0]);
	}
}

int DatabaseManager::GenerateRandomId() const
{
	std::random_device rd;

	std::default_random_engine engine(rd());

	auto count = m_db.count<WordsEntity>();

	std::uniform_int_distribution<int> distribution(0, count - 1);

	return distribution(engine);
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
