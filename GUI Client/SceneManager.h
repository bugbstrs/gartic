#pragma once

#include <QStackedWidget>

class SceneManager  : public QStackedWidget
{
	Q_OBJECT

public:
	SceneManager(QWidget *parent);
	~SceneManager();
};
