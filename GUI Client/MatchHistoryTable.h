#pragma once

#include <Qt6/QtWidgets/QTableWidget>
#include <Qt6/QtWidgets/QLineEdit>

class MatchHistoryTable : public QTableWidget
{
	Q_OBJECT

public:
	//Constructor
	MatchHistoryTable(QWidget *parent = nullptr);

	//Destructor
	~MatchHistoryTable();

	int GetBestScore() const noexcept;
	float GetAverageScore() const noexcept;

protected:
	void showEvent(QShowEvent* event) override;

signals:
	void OnScoresUpdated(int bestScore, float averageScore);

private:
	const int m_columnsNumber = 2;
	int m_bestScore;
	float m_averageScore;
};
