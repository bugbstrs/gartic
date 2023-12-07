#include "User.h"

http::User::User(const std::string& newUsername):
	m_username{ newUsername }
{
}

std::string http::User::GetUsername() const noexcept
{
	return m_username;
}

Time http::User::GetTime() const noexcept
{
	return m_active;
}

void http::User::SetActive()
{
	m_active.SetStartValue(kSecondsForBeingActive);
}
