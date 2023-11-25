#include "RouteManager.h"

void http::RouteManager::Run()
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
	});

	m_app.port(18080).multithreaded().run();
}
