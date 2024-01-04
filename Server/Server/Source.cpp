#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>

#include "RouteManager.h"
#include "Game.h"
#include "Time.h"

using namespace http;

int main()
{
	GarticStorage storage;
	
    if (!storage.Initialize())
	{
		std::cout << "[ERROR] Failed to initialize the database!";
		return -1;
	}

	GarticManager garticManager;

	RouteManager manager(storage, garticManager);

	Time::CheckTimers();

	manager.Run();

	return 0;
}