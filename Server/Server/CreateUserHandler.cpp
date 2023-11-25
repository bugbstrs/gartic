#include "CreateUserHandler.h"

http::CreateUserHandler::CreateUserHandler(GarticStorage& storage): m_db(storage)
{
}

crow::response http::CreateUserHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto username = bodyArgs.find("username");
	auto password = bodyArgs.find("password");
	auto points = bodyArgs.find("points");
	auto gamesPlayed = bodyArgs.find("games played");
	
	if (gamesPlayed != end && points != end && username != end && password != end)
	{
		m_db.CreateUser(std::stoi(gamesPlayed->second), std::stoi(points->second), username->second, password->second);
		return crow::response(201); 
	}
	
	return crow::response(401);
}
