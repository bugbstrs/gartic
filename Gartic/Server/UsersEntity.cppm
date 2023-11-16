export module UsersEntity;

import <cstdint>;
import <string>;

using String = std::string;

export class UsersEntity
{
public:
	UsersEntity() = default;
	UsersEntity(uint16_t newId, const String& newUsername, const String& newPassword);

	~UsersEntity() = default;

	uint16_t GetId() const;
	String GetUsername() const;
	String GetPassword() const;

private:
	uint16_t id;
	String username;
	String password;
};