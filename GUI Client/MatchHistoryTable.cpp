#include "MatchHistoryTable.h"
#include "UserCredentials.h"

#include<crow.h>

MatchHistoryTable::MatchHistoryTable(QWidget* parent)
	: QTableWidget{ parent }
{
	GetMatchHistoryFromDatabase();
}

MatchHistoryTable::~MatchHistoryTable()
{}

void MatchHistoryTable::showEvent(QShowEvent* event)
{
	auto profileInfo = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchprofileinfo" },
		cpr::Parameters{
			{"username", UserCredentials::GetUsername()},
			{"password", UserCredentials::GetPassword()}
		}
	);

	auto profileInfoVector = crow::json::load(profileInfo.text);

	int nrOfMatches = profileInfoVector["info"].size();
	setColumnCount(m_columnsNumber);
	setRowCount(nrOfMatches);

	for (int row = 0; row < nrOfMatches; ++row) {
		QTableWidgetItem* positionItem = new QTableWidgetItem(QString::fromUtf8(std::string(profileInfoVector["info"][row][0])));
		positionItem->setTextAlignment(Qt::AlignCenter);
		setItem(row, 0, positionItem);

		QTableWidgetItem* pointsItem = new QTableWidgetItem(QString::fromUtf8(std::string(profileInfoVector["info"][row][1])));
		pointsItem->setTextAlignment(Qt::AlignCenter);
		setItem(row, 1, pointsItem);
	}
}

QString MatchHistoryTable::GetRowInfoForColumnWithIndex(uint16_t index, const Row& row) const noexcept
{
	if (index == 0)
		return row.ranking;
	else
		return row.points;
}

void MatchHistoryTable::GetMatchHistoryFromDatabase() noexcept
{
	for (int row = 0; row < 2; ++row) {
		matches.push_back(Row("1st", "574"));
		matches.push_back(Row("4th", "371"));
	}
}
