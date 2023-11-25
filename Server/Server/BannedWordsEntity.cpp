#include "BannedWordsEntity.h"

http::BannedWordsEntity::BannedWordsEntity(const std::string& newName) : name{newName}
{
}

void http::BannedWordsEntity::SetId(int newId)
{
	id = newId;
}

void http::BannedWordsEntity::SetName(const std::string& newName)
{
	name = newName;
}

int http::BannedWordsEntity::GetId() const
{
	return id;
}

std::string http::BannedWordsEntity::GetName() const
{
	return name;
}
