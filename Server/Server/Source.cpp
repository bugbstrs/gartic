#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>

#include "Server/RouteManager.h"

//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest/doctest.h";

using namespace http;

int main(int argc, char** argv)
{
    //if (argc == 2 && strcmp("test", argv[1]) == 0)
    //{
    //    doctest::Context ctx;
    //    ctx.setOption("abort-after", 1);
    //    ctx.applyCommandLine(argc, argv);
    //    ctx.setOption("no-breaks", true);
    //    return ctx.run();
    //}

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