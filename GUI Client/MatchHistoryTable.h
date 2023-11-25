#pragma once

#include <QTableWidget>

class MatchHistoryTable : public QTableWidget
{
	Q_OBJECT

public:
	//Constructors
	MatchHistoryTable(QWidget *parent = nullptr);
	~MatchHistoryTable();

protected:
	void showEvent(QShowEvent* event);

private:
	struct Row {
		Row(const std::string& ranking, const std::string& points, const std::string& date) :
			ranking(QString::fromStdString(ranking)),
			points(QString::fromStdString(points)),
			date(QString::fromStdString(date))
		{}

		QString ranking;
		QString points;
		QString date;
	};

	QString GetRowInfoForColumnWithIndex(uint8_t index, const Row& row);
	void GetMatchHistoryFromDatabase();
private:
	std::vector <Row> matches;
};
