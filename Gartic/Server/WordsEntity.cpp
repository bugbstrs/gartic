#include "WordsEntity.h"

WordsEntity::WordsEntity(const std::string& newName):
    name(newName)
{
}

void WordsEntity::SetName(const std::string& newName)
{
    this->name = newName;
}

void WordsEntity::SetId(int newId)
{
    this->id = newId;
}

int WordsEntity::GetId() const
{
    return id;
}

std::string WordsEntity::GetName() const
{
    return name;
}
