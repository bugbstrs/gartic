#include <crow.h>
#include "GarticDatabase.h"

namespace http
{
	class RouteManager
	{
	public:
		void Run(GarticStorage& storage);

	private:
		crow::SimpleApp m_app;
	};
}