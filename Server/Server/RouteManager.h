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
		// Constructors
        RouteManager() = delete;
        RouteManager(GarticStorage& storage, GarticManager& manager);

		// Route creation
		void Run();

	private:
		// Database related
		void FetchWordRoute();
		void FetchQuoteRoute();
		void FetchAllWordsRoute();
		void FetchAllUsersRoute();
		void FetchTop5UsersRoute();
		void LoginRoute();
		void RegisterRoute();
		void CheckBannedWordRoute();

        std::optional<crow::response> IsRequestAuthenticatedRoute(const crow::request& request);

		// Logic related
		void CreateLobbyRoute();
		void CreateGameRoute();
		
		// Lobby
		void FetchCodeRoute();
		void FetchUsersRoute();
		void FetchSettingsRoute();

		// Game
		void FetchPlayersRoute();
		void FetchGameStatusRoute();
		void FetchRoundNumberRoute();
		void FetchDrawerRoute();

		void PutWordToGuessRoute();
		void GetWordToDisplayRoute();

	private:
		crow::SimpleApp m_app;
        GarticStorage& m_storage;

		GarticManager& m_gartic;
	};
}