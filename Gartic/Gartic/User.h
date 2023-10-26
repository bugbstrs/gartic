#pragma once
#include <string>
class User
{
public:
	User();
	User(const std::string& username, uint64_t credits, bool isPlaying);
	void SetUsername(const std::string& username);
	std::string GetUsername() const;
private:
	std::string m_username;
	uint64_t m_credits;
	bool m_isPlaying;
};

