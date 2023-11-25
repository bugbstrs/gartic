#pragma once

#include<crow.h>

#include "GarticDatabase.h"

namespace http
{
	class CreateUserHandler
	{
	public:
		CreateUserHandler(GarticStorage& storage);

		crow::response operator()(const crow::request& req) const;

	private:
		GarticStorage& m_db;
	};
}