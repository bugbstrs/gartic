
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::on_playButton_released()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_quitButton_released()
{
    QCoreApplication::quit();
}

void MainWindow::on_redColorButton_released()
{
    ui->drawingBoardCanvas->changePenColor(Qt::red);
}

void MainWindow::on_leaveGameButton_released()
{
    ui->stackedWidget->setCurrentIndex(0);
}

