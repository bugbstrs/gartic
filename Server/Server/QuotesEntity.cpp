#include "QuotesEntity.h"

http::QuotesEntity::QuotesEntity(const std::string& newName) : name{newName}
{
}

void http::QuotesEntity::SetId(int newId)
{
	id = newId;
}

void http::QuotesEntity::SetName(const std::string& newName)
{
	name = newName;
}

int http::QuotesEntity::GetId() const
{
	return id;
}

std::string http::QuotesEntity::GetName() const
{
	return name;
}
