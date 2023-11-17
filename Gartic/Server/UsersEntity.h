#pragma once
#include <string>

class UsersEntity
{
public:
	UsersEntity() = default;
	UsersEntity(int newGamesPlayed, int newPoints, const std::string& newUsername, const std::string& newPassword);

	~UsersEntity() = default;

	void SetId(int id);
	void SetGamesPlayed(int gamesPlayed);
	void SetPoints(int points);
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	
	int GetId() const;
	int GetGamesPlayed() const;
	int GetPoints() const;
	std::string GetUsername() const;
	std::string GetPassword() const;
	
private:
	int id;
	int gamesPlayed;
	int points;
	std::string username;
	std::string password;
};