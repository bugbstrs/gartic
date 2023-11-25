#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>

#include "Server/RouteManager.h"

using namespace http;

int main()
{
	GarticStorage storage;
	if (!storage.Initialize())
	{
		std::cout << "[ERROR] Failed to initialize the database!";
		return -1;
	}

	RouteManager manager;

	manager.Run(storage);

	return 0;
}