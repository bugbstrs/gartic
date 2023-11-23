#include "RouteManager.h"

void http::RouteManager::Run(GarticStorage& storage)
{
	CROW_ROUTE(m_app, "BugBusters_Gartic/")([]() {
		return "";
	});
}
