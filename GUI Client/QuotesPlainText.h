#pragma once

#include <QPlainTextEdit>

class QuotesPlainText  : public QPlainTextEdit
{
	Q_OBJECT

public:
	QuotesPlainText(QWidget *parent);
	~QuotesPlainText();

	void showEvent(QShowEvent* event) override;

private:
	bool firstShow{ true };
};
