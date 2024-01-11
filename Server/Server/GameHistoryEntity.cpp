#include "GameHistoryEntity.h"

http::GameHistoryEntity::GameHistoryEntity(int newId, int newUserId, int newPosition, int newTotalPoints):
	id{ newId },
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

int http::GameHistoryEntity::GetId()
{
	return id;
}

int http::GameHistoryEntity::GetUserId()
{
	return userId;
}

int http::GameHistoryEntity::GetPosition()
{
	return position;
}

int http::GameHistoryEntity::GetTotalPoints()
{
	return totalPoints;
}
