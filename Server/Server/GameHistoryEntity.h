#pragma once

namespace http
{
	class GameHistoryEntity
	{
	public:
		GameHistoryEntity() = default;
		GameHistoryEntity(int newId, int newUserId, int newPosition, int newTotalPoints);

		~GameHistoryEntity() = default;

		void SetId(int newId);
		void SetUserId(int newUserId);
		void SetPosition(int newPosition);
		void SetTotalPoints(int newTotalPoints);

		int GetId();
		int GetUserId();
		int GetPosition();
		int GetTotalPoints();

	private:
		int id;
		int userId;
		int position;
		int totalPoints;
	};
}

