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

signals:
	void ColorChanged(QColor color);

private:
	QPushButton* button;
};
