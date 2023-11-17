export module UsersEntity;

import <cstdint>;
import <string>;
import <vector>;

using String = std::string;
using Vector = std::vector<uint16_t>;

export class UsersEntity
{
public:
	UsersEntity() = default;
	UsersEntity(uint16_t newId, const String& newUsername, const String& newPassword);

	~UsersEntity() = default;

	uint16_t GetId() const;
	uint16_t GetGamesPlayed() const;
	uint16_t GetPoints() const;
	String GetUsername() const;
	String GetPassword() const;
	Vector GetPrevScores() const;

private:
	uint16_t id;
	uint16_t gamesPlayed;
	uint16_t points;
	String username;
	String password;
	Vector previousScores;
};