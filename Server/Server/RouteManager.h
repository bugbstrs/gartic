#include <crow.h>

#include "GarticDatabase.h"
#include "Game.h"

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
		void CreatePutWordToGuessRoute(GarticStorage& storage);
		void CreateGetWordToDisplayRoute(GarticStorage& storage);

	private:
		crow::SimpleApp m_app;

		Game m_game;
	};
}