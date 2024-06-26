#pragma once

#include <Qt6/QtWidgets/QPlainTextEdit>

class QuotesPlainText  : public QPlainTextEdit
{
	Q_OBJECT

public:
	QuotesPlainText(QWidget *parent);
	~QuotesPlainText();

	void showEvent(QShowEvent* event) override;

private:
	bool m_firstShow{ true };
};
