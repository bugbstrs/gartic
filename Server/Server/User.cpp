#include "User.h"

http::User::User(const std::string& newUsername):
	m_username{ newUsername }
{
}

std::string http::User::GetUsername() const noexcept
{
	return m_username;
}

void http::User::SetActive()
{
	m_active.SetStartValue(kSecondsForBeingActive);
	m_active.SetStartTimeStamp(m_active.GetServerTime());
}
