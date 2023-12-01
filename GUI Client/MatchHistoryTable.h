#pragma once

#include <QTableWidget>

class MatchHistoryTable : public QTableWidget
{
	Q_OBJECT

public:
	//Constructor
	MatchHistoryTable(QWidget *parent = nullptr);

	//Destructor
	~MatchHistoryTable();

protected:
	void showEvent(QShowEvent* event);

private:
	struct Row {
		Row(const std::string& ranking, const std::string& points, const std::string& date) :
			ranking(QString::fromUtf8(ranking)),
			points(QString::fromUtf8(points)),
			date(QString::fromUtf8(date))
		{}

		QString ranking;
		QString points;
		QString date;
	};

	QString GetRowInfoForColumnWithIndex(uint16_t index, const Row& row);
	void GetMatchHistoryFromDatabase();
private:
	std::vector <Row> matches;
};
