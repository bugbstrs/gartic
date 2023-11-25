#include "CreateUserHandler.h"

http::CreateUserHandler::CreateUserHandler(GarticStorage& storage): m_db(storage)
{
}

crow::response http::CreateUserHandler::operator()(const crow::request& req) const
{
    const crow::query_string& bodyArgs    = req.url_params;
    char*                     gamesPlayed = bodyArgs.get("games played");
    char*                     password    = bodyArgs.get("password");
    char*                     points      = bodyArgs.get("points");
    char*                     username    = bodyArgs.get("username");
    
    if (gamesPlayed == nullptr || password == nullptr)
    {
        // todo: log
        return crow::response(401);
    }
    if (points == nullptr || username == nullptr)
    {
        // todo: log
        return crow::response(400);
    }

    try
    {
        m_db.CreateUser(std::stoi(gamesPlayed), std::stoi(points), String(username), String(password));
        return crow::response(201);
    }
    catch (std::invalid_argument invalidArgumentException)
    {
        // todo: log with useful info
        return crow::response(400);
    }
    catch (std::out_of_range outOfRangeException)
    {
        // todo: log with useful info
        return crow::response(400);
    }
}
