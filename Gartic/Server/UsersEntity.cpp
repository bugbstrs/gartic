module UsersEntity;

UsersEntity::UsersEntity(uint16_t newId, const String& newUsername, const String& newPassword):
	id(newId),
	username(newUsername),
	password(newPassword)
{
}

uint16_t UsersEntity::GetId() const
{
	return id;
}

uint16_t UsersEntity::GetGamesPlayed() const
{
	return gamesPlayed;
}

uint16_t UsersEntity::GetPoints() const
{
	return points;
}

String UsersEntity::GetUsername() const
{
	return username;
}

String UsersEntity::GetPassword() const
{
	return password;
}

Vector UsersEntity::GetPrevScores() const
{
	return previousScores;
}

