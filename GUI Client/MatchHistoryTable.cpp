#include "MatchHistoryTable.h"
#include "UserCredentials.h"

#include<crow.h>

MatchHistoryTable::MatchHistoryTable(QWidget* parent)
	: QTableWidget{ parent }
{}

MatchHistoryTable::~MatchHistoryTable()
{}

int MatchHistoryTable::GetBestScore() const noexcept
{
	return m_bestScore;
}

float MatchHistoryTable::GetAverageScore() const noexcept
{
	return m_averageScore;
}

void MatchHistoryTable::showEvent(QShowEvent* event)
{
	auto profileInfo = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchprofileinfo" },
		cpr::Parameters{
			{"username", UserCredentials::GetUsername()},
			{"password", UserCredentials::GetPassword()}
		}
	);

	if (profileInfo.status_code == 200) {
		auto profileInfoVector = crow::json::load(profileInfo.text);

		int nrOfMatches = profileInfoVector["info"].size();
		setColumnCount(m_columnsNumber);
		setRowCount(nrOfMatches);

		m_bestScore = std::stoi(std::string(profileInfoVector["info"][0]["points"]));
		m_averageScore = 0;

		for (int row = 0; row < nrOfMatches; ++row) {
			int matchPoints = std::stoi(std::string(profileInfoVector["info"][row]["points"]));

			if (matchPoints > m_bestScore)
				m_bestScore = matchPoints;
			m_averageScore += matchPoints;

			QTableWidgetItem* positionItem = new QTableWidgetItem(QString::fromUtf8(std::string(profileInfoVector["info"][row]["rank"])));
			QTableWidgetItem* pointsItem = new QTableWidgetItem(QString::number(matchPoints));

			positionItem->setTextAlignment(Qt::AlignCenter);
			setItem(row, 0, positionItem);

			pointsItem->setTextAlignment(Qt::AlignCenter);
			setItem(row, 1, pointsItem);
		}
		m_averageScore /= nrOfMatches;
	}
}
