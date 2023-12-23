#include <crow.h>

#include "GarticDatabase.h"
#include "Lobby.h"
#include <optional>

namespace http
{
	class RouteManager
	{
	public:
        RouteManager() = delete;
        RouteManager(GarticStorage& storage);
		void Run();

	private:
		void CreateFetchWordRoute();
		void CreateFetchQuoteRoute();
		void CreateFetchAllWordsRoute();
		void CreateFetchAllUsersRoute();
		void CreateFetchTop5UsersRoute();
		void CreateLoginRoute();
		void CreateRegisterRoute();
		void CreateCheckBannedWordRoute();
		void CreatePutWordToGuessRoute();
		void CreateGetWordToDisplayRoute();

        std::optional<crow::response> IsRequestAuthenticated(const crow::request& request);

	private:
		crow::SimpleApp m_app;
        GarticStorage& m_storage;
	};
}