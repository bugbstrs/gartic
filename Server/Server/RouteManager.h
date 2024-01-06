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

        crow::response IsRequestAuthenticated(const crow::request& request);

		// Gartic Manager related
		void CreateLobbyRoute();
		void CreateGameRoute();

		// Lobby
		void JoinLobbyRoute(); 
		void FetchCodeRoute();
		void FetchUsersRoute();
		void SetSettingsRoute();
		void FetchSettingsRoute();
		void FetchLobbyStatusRoute();
		
		void LeaveLobbyRoute();

		// Game
		void FetchPlayersRoute();
		void FetchGameStatusRoute();
		void FetchRoundNumberRoute();
		void FetchDrawerRoute();
		void FetchNWordsRoute();
		void FetchDrawingBoard();
		void FetchWordToGuessRoute();
		void FetchWordToDisplayRoute();
		void FetchMessagesRoute();

		void LeaveGameRoute();

		void PutWordToGuessRoute();
		void PutMessageInChatRoute();

	private:
		crow::SimpleApp m_app;
        GarticStorage& m_storage;

		GarticManager& m_gartic;
	};
}