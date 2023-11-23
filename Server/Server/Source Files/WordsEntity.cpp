#include "../Header Files/WordsEntity.h"

using namespace http;

WordsEntity::WordsEntity(const std::string& newName):
    name{ newName }
{}

void WordsEntity::SetId(int newId)
{
    this->id = newId;
}

void WordsEntity::SetName(const std::string& newName)
{
    this->name = newName;
}

int WordsEntity::GetId() const
{
    return id;
}

std::string WordsEntity::GetName() const
{
    return name;
}
