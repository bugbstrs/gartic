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

	void ResetCurrentColorView();

public slots:
	void showEvent(QShowEvent* event) override;
	void OnColorChange() noexcept;
	void OnWidthChange() noexcept;
	void OnCanvasCleared() noexcept;
	void OnUndoButtonReleased() noexcept;
	void OnFillButtonReleased() noexcept;
	void OnEraserButtonReleased() noexcept;
	void OnPencilButtonReleased() noexcept;

signals:
	void OnColorChangedSignal(QColor color);
	void OnWidthChangedSignal(int width);
	void OnCanvasClearedSignal();
	void OnUndoButtonReleasedSignal();
	void OnFillButtonReleasedSignal();
	void OnEraserButtonReleasedSignal();
	void OnPencilButtonReleasedSignal();

private:
	bool m_firstShow{ true };
	QWidget* m_currentColorView { new QWidget{} };
	const QString kSmallWidthButton{ "smallWidthButton" };
	const QString kMediumWidthButton{ "mediumWidthButton" };
	const QString kLargeWidthButton{ "largeWidthButton" };
	const QString kExtraLargeWidthButton{ "extraLargeWidthButton" };
};
