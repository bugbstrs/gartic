#pragma once
#include <string>

namespace http
{
	class UsersEntity
	{
	public:
		UsersEntity() = default;
		UsersEntity(int newPoints, const std::string& newUsername, const std::string& newPassword);

		~UsersEntity() = default;

		void SetGamesPlayed(int gamesPlayed);
		void SetId(int id);
		void SetPassword(const std::string& password);
		void SetPoints(int points);
		void SetUsername(const std::string& username);

		int			GetId()			 const;
		int			GetPoints()		 const;
		std::string GetPassword()	 const;
		std::string GetUsername()	 const;

		bool operator==(const UsersEntity& secondUser) const noexcept;

	private:
		int			id;
		int			points;
		std::string password;
		std::string username;
	};
}