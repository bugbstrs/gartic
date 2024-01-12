#include "MatchHistoryTable.h"

MatchHistoryTable::MatchHistoryTable(QWidget *parent)
	: QTableWidget{ parent }
{
	GetMatchHistoryFromDatabase(); 
}

MatchHistoryTable::~MatchHistoryTable()
{}

void MatchHistoryTable::showEvent(QShowEvent * event)
{
	//apelezi ruta si convertesti la fel ca la cafeulta si apelezi ca mai sus
	int nrOfMatches = 2;
	setColumnCount(m_columnsNumber);
	setRowCount(nrOfMatches);
	for (int row = 0; row < nrOfMatches; ++row) {
		for (int col = 0; col < m_columnsNumber; ++col) {
			QTableWidgetItem* item = new QTableWidgetItem(GetRowInfoForColumnWithIndex(col, matches[row]));
			item->setTextAlignment(Qt::AlignCenter);
			setItem(row, col, item);
		}
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
