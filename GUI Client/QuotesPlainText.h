#pragma once

#include <QPlainTextEdit>

class QuotesPlainText  : public QPlainTextEdit
{
	Q_OBJECT

public:
	QuotesPlainText(QWidget *parent);
	~QuotesPlainText();

public slots:
	void showEvent(QShowEvent* event) override;
};
