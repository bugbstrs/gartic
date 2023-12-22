#include "ScoreboardTable.h"
#include <random>

ScoreboardTable::ScoreboardTable(QWidget *parent)
	: QTableWidget{ parent }
{
	nameFont.setFamily("Consolas");
	pointsFont.setFamily("Consolas");
	nameFont.setPixelSize(12);
	pointsFont.setPixelSize(20);
}

ScoreboardTable::~ScoreboardTable()
{}

void ScoreboardTable::AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor>> takenAvatars)
{
	for (auto& avatar : takenAvatars) {
		QTableWidgetItem* name = new QTableWidgetItem(std::get<0>(avatar), std::get<1>(avatar));
		QTableWidgetItem* score = new QTableWidgetItem(QString::number(0));
		name->setBackground(std::get<2>(avatar));
		name->setFont(nameFont);
		name->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		score->setBackground(std::get<2>(avatar));
		score->setFont(pointsFont);
		score->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		int rowPosition = rowCount();
		insertRow(rowPosition);
		setItem(rowPosition, 0, name);
		setItem(rowPosition, 1, score);
		players.push_back({name, score});
	}
}

void ScoreboardTable::AddPointsToPlayerWithIndex(uint8_t index)
{
	players[0].second->setText(QString::number(players[0].second->text().toInt() + 10));
}

void ScoreboardTable::ClearScoreboard()
{
	players.clear();
	clearContents();
}
