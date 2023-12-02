#include <crow.h>

#include "GarticDatabase.h"
#include "OngoingGame.h"

namespace http
{
	class RouteManager
	{
	public:
        RouteManager() = default;
		void Run(GarticStorage& storage);

	private:
		void CreateFetchWordRoute(GarticStorage& storage);
		void CreateFetchQuoteRoute(GarticStorage& storage);
		void CreateFetchAllWordsRoute(GarticStorage& storage);
		void CreateFetchAllUsersRoute(GarticStorage& storage);
		void CreateFetchTop5UsersRoute(GarticStorage& storage);
		void CreateLoginRoute(GarticStorage& storage);
		void CreateRegisterRoute(GarticStorage& storage);
		void CreateCheckBannedWordRoute(GarticStorage& storage);

	private:
		crow::SimpleApp m_app;

		OngoingGame m_game;
	};
}