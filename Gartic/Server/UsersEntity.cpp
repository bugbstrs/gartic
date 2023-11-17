#include "UsersEntity.h"

UsersEntity::UsersEntity(int newId, const std::string& newUsername, const std::string& newPassword):
	id(newId),
	username(newUsername),
	password(newPassword)
{
}

void UsersEntity::SetId(int id)
{
	this->id = id;
}

void UsersEntity::SetGamesPlayed(int gamesPlayed)
{
	this->gamesPlayed = gamesPlayed;
}

void UsersEntity::SetPoints(int points)
{
	this->points = points;
}

void UsersEntity::SetUsername(const std::string& username)
{
	this->username = username;
}

void UsersEntity::SetPassword(const std::string& password)
{
	this->password = password;
}

int UsersEntity::GetId() const
{
	return id;
}

int UsersEntity::GetGamesPlayed() const
{
	return gamesPlayed;
}

int UsersEntity::GetPoints() const
{
	return points;
}

std::string UsersEntity::GetUsername() const
{
	return username;
}

std::string UsersEntity::GetPassword() const
{
	return password;
}

