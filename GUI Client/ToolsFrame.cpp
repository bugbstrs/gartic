#include "ToolsFrame.h"

ToolsFrame::ToolsFrame(QWidget *parent)
	: QFrame(parent)
{}

ToolsFrame::~ToolsFrame()
{}

void ToolsFrame::OnColorChange()
{
	emit OnColorChangedSignal(qobject_cast<QPushButton*>(sender())->palette().color(QPalette::Button));
}

void ToolsFrame::OnWidthChange()
{
	int width;
	QString buttonName = qobject_cast<QPushButton*>(sender())->objectName();
	if (buttonName == kSmallWidthButton)
		width = 4;
	else if (buttonName == kMediumWidthButton)
		width = 10;
	else if (buttonName == kLargeWidthButton)
		width = 18;
	else width = 26;
	emit OnWidthChangedSignal(width);
}

void ToolsFrame::OnCanvasCleared() {
	emit OnCanvasClearedSignal();
}

void ToolsFrame::showEvent(QShowEvent* event) {
	QObject::connect(findChild<QPushButton*>("blackColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("whiteColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("grayColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkGrayColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("redColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkRedColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("orangeColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkOrangeColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("yellowColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkYellowColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("greenColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkGreenColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("skyBlueColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkSkyBlueColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	
	QObject::connect(findChild<QPushButton*>("blueColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkBlueColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("purpleColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkPurpleColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("pinkColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkPinkColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("brownColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);
	QObject::connect(findChild<QPushButton*>("darkBrownColorButton"), &QPushButton::released, this, &ToolsFrame::OnColorChange);

	QObject::connect(findChild<QPushButton*>("smallWidthButton"), &QPushButton::released, this, &ToolsFrame::OnWidthChange);
	QObject::connect(findChild<QPushButton*>("mediumWidthButton"), &QPushButton::released, this, &ToolsFrame::OnWidthChange);
	QObject::connect(findChild<QPushButton*>("largeWidthButton"), &QPushButton::released, this, &ToolsFrame::OnWidthChange);
	QObject::connect(findChild<QPushButton*>("extraLargeWidthButton"), &QPushButton::released, this, &ToolsFrame::OnWidthChange);

	QObject::connect(findChild<QPushButton*>("clearDrawingBoardButton"), &QPushButton::released, this, &ToolsFrame::OnCanvasClearedSignal);
}