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

String UsersEntity::GetUsername() const
{
	return username;
}

String UsersEntity::GetPassword() const
{
	return password;
}

