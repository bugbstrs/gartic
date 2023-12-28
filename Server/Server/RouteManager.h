#include <crow.h>

#include "GarticDatabase.h"
#include "GarticManager.h"
#include "Lobby.h"
#include <optional>

namespace http
{
	class RouteManager
	{
	public:
        RouteManager() = delete;
        RouteManager(GarticStorage& storage, GarticManager& manager);
		void Run();

	private:
		// Database related
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

		// Logic related
		void CreateLobbyRoute();
		void CreateGameRoute();

	private:
		crow::SimpleApp m_app;
        GarticStorage& m_storage;

		GarticManager& m_gartic;
	};
}