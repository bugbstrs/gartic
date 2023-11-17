module UsersEntity;

UsersEntity::UsersEntity(uint16_t newId, const String& newUsername, const String& newPassword):
	id(newId),
	username(newUsername),
	password(newPassword)
{
}

void UsersEntity::SetId(uint16_t id)
{
	this->id = id;
}

void UsersEntity::SetGamesPlayed(uint16_t gamesPlayed)
{
	this->gamesPlayed = gamesPlayed;
}

void UsersEntity::SetPoints(uint16_t points)
{
	this->points = points;
}

void UsersEntity::SetUsername(const String& username)
{
	this->username = username;
}

void UsersEntity::SetPassword(const String& password)
{
	this->password = password;
}

void UsersEntity::SetPrevScores(const Vector& previousScores)
{
	this->previousScores = previousScores;
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

