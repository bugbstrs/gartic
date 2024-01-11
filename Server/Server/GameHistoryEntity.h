#pragma once

namespace http
{
	class GameHistoryEntity
	{
	public:
		GameHistoryEntity() = default;
		GameHistoryEntity(int newUserId, int newPosition, int newTotalPoints);

		~GameHistoryEntity() = default;

		void SetId(int newId);
		void SetUserId(int newUserId);
		void SetPosition(int newPosition);
		void SetTotalPoints(int newTotalPoints);

		int GetId() const;
		int GetUserId() const;
		int GetPosition() const;
		int GetTotalPoints() const;

	private:
		int id;
		int userId;
		int position;
		int totalPoints;
	};
}

