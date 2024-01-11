#include "GameHistoryEntity.h"

http::GameHistoryEntity::GameHistoryEntity(int newUserId, int newPosition, int newTotalPoints):
	userId{ newUserId },
	position{ newPosition },
	totalPoints{ newTotalPoints }
{
}

void http::GameHistoryEntity::SetId(int newId)
{
	id = newId;
}

void http::GameHistoryEntity::SetUserId(int newUserId)
{
	userId = newUserId;
}

void http::GameHistoryEntity::SetPosition(int newPosition)
{
	position = newPosition;
}

void http::GameHistoryEntity::SetTotalPoints(int newTotalPoints)
{
	totalPoints = newTotalPoints;
}

int http::GameHistoryEntity::GetId() const
{
	return id;
}

int http::GameHistoryEntity::GetUserId() const
{
	return userId;
}

int http::GameHistoryEntity::GetPosition() const
{
	return position;
}

int http::GameHistoryEntity::GetTotalPoints() const
{
	return totalPoints;
}
