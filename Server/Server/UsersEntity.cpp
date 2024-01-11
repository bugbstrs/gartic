#include "UsersEntity.h"

using namespace http;

UsersEntity::UsersEntity(int newPoints, const std::string& newUsername, const std::string& newPassword):
	points		{ newPoints		 },
	username	{ newUsername	 },
	password	{ newPassword	 }
{}

void UsersEntity::SetId(int id)
{
	this->id = id;
}

void UsersEntity::SetPassword(const std::string& password)
{
	this->password = password;
}

void UsersEntity::SetPoints(int points)
{
	this->points = points;
}

void UsersEntity::SetUsername(const std::string& username)
{
	this->username = username;
}

int UsersEntity::GetId() const
{
	return id;
}

int UsersEntity::GetPoints() const
{
	return points;
}

std::string UsersEntity::GetPassword() const
{
	return password;
}

std::string UsersEntity::GetUsername() const
{
	return username;
}

bool http::UsersEntity::operator==(const UsersEntity& secondUser) const noexcept
{
	return this->points == secondUser.points		   && 
		   this->username == secondUser.username       && 
		   this->password == secondUser.password       && 
		   this->id == secondUser.id;
}
