#pragma once

#include <QFrame>
#include <qpushbutton.h>
#include <unordered_map>

class ToolsFrame  : public QFrame
{
	Q_OBJECT

public:
	ToolsFrame(QWidget *parent = nullptr);
	~ToolsFrame();

public slots:
	void showEvent(QShowEvent* event);
	void OnColorChange();
	void OnWidthChange();

signals:
	void ColorChanged(QColor color);
	void WidthChanged(int width);

private:
	QPushButton* button;
	const QString kSmallWidthButton = "smallWidthButton";
	const QString kMediumWidthButton = "mediumWidthButton";
	const QString kLargeWidthButton = "largeWidthButton";
	const QString kExtraLargeWidthButton = "extraLargeWidthButton";
};
