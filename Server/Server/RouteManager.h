#include <crow.h>
#include "GarticDatabase.h"

namespace http
{
	class RouteManager
	{
	public:
		void Run();

	private:
		crow::SimpleApp m_app;
	};
}