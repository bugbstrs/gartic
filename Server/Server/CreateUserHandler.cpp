#include "CreateUserHandler.h"

http::CreateUserHandler::CreateUserHandler(GarticStorage& storage): m_db(storage)
{
}

crow::response http::CreateUserHandler::operator()(const crow::request& req) const
{
    const crow::query_string& bodyArgs    = req.url_params;
    char*                     password    = bodyArgs.get("password");
    char*                     username    = bodyArgs.get("username");
    
    if (password == nullptr || username == nullptr)
    {
        // todo: log
        return crow::response(401);
    }

    m_db.CreateUser(String(username), String(password));
    return crow::response(201);
}
