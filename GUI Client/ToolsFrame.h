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
	void OnUndoButtonReleased();
	void OnFillButtonReleased();
	void OnEraserButtonReleased();
	void OnPencilButtonReleased();

signals:
	void OnColorChangedSignal(QColor color);
	void OnWidthChangedSignal(int width);
	void OnCanvasClearedSignal();
	void OnUndoButtonReleasedSignal();
	void OnFillButtonReleasedSignal();
	void OnEraserButtonReleasedSignal();
	void OnPencilButtonReleasedSignal();

private:
	QWidget* currentColorView;
	const QString kSmallWidthButton = "smallWidthButton";
	const QString kMediumWidthButton = "mediumWidthButton";
	const QString kLargeWidthButton = "largeWidthButton";
	const QString kExtraLargeWidthButton = "extraLargeWidthButton";
};
