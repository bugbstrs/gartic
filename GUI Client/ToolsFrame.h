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
	void OnCanvasCleared();

signals:
	void OnColorChangedSignal(QColor color);
	void OnWidthChangedSignal(int width);
	void OnCanvasClearedSignal();

private:
	QPushButton* button;
	const QString kSmallWidthButton = "smallWidthButton";
	const QString kMediumWidthButton = "mediumWidthButton";
	const QString kLargeWidthButton = "largeWidthButton";
	const QString kExtraLargeWidthButton = "extraLargeWidthButton";
};