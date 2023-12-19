#include <crow.h>

#include "GarticDatabase.h"
#include "Lobby.h"
#include <optional>

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

        std::optional<crow::response> IsRequestAuthenticated(const crow::request& request);

	private:
		crow::SimpleApp m_app;
	};
}