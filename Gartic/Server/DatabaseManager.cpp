#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(Storage& storage): m_db(storage)
{
}

void DatabaseManager::PopulateWordsEntity()
{
    WordVector words;

    std::ifstream filename;
    filename.open("words.txt");
    
    std::string word;
    
    while (filename >> word) 
    {
        words.push_back(word);
    }

    for (const auto& w : words) 
    {
        m_db.insert(WordsEntity{ w });
    }

    filename.close();
}

void DatabaseManager::PopulateUsersEntity()
{
}
