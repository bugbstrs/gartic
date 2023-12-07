#pragma once

#include <string>

#include "Time.h"

namespace http
{
	class User
	{
	public:
		User() = default;
		User(const std::string& m_username);

		~User() = default;

		std::string GetUsername() const noexcept;
		Time GetTime() const noexcept;

		void SetActive();

	private:
		const int kSecondsForBeingActive = 5;

	private:
		std::string m_username;

		Time Active;
	};
}

