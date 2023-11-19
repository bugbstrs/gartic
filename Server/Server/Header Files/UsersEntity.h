#pragma once
#include <string>

class UsersEntity
{
public:
	UsersEntity() = default;
	UsersEntity(int newGamesPlayed, int newPoints, const std::string& newUsername, const std::string& newPassword);

	~UsersEntity() = default;

	void SetGamesPlayed (int gamesPlayed);
	void SetId			(int id);
	void SetPassword	(const std::string& password);
	void SetPoints		(int points);
	void SetUsername	(const std::string& username);
	
	int			GetGamesPlayed() const;
	int			GetId()			 const;
	int			GetPoints()		 const;
	std::string GetPassword()	 const;
	std::string GetUsername()	 const;
	
private:
	int			gamesPlayed;
	int			id;
	int			points;
	std::string password;
	std::string username;
};