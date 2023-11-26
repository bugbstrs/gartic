#include <crow.h>
#include "GarticDatabase.h"

namespace http
{
	class RouteManager
	{
	public:
		void Run(GarticStorage& storage);

	private:
		void CreateFetchWordRoute(GarticStorage& storage);
		void CreateFetchQuoteRoute(GarticStorage& storage);
		void CreateFetchAllWordsRoute(GarticStorage& storage);
		void CreateFetchAllUsersRoute(GarticStorage& storage);
		void CreateLoginRoute(GarticStorage& storage);
		void CreateRegisterRoute(GarticStorage& storage);
		void CreateCheckBannedWordRoute(GarticStorage& storage);

	private:
		crow::SimpleApp m_app;
	};
}