#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>

#include "Server/RouteManager.h"
#include "Game.h"

using namespace http;

int main()
{
	GarticStorage storage;
	
    if (!storage.Initialize())
	{
		std::cout << "[ERROR] Failed to initialize the database!";
		return -1;
	}

	RouteManager manager(storage);

	manager.Run();

	return 0;
}