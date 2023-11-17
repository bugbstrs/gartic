
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->frame_2->hide();
    //    ui->frame_2->setEnabled(false);
}

MainWindow::~MainWindow() = default;

void MainWindow::on_pushButton_released()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_released()
{
    QCoreApplication::quit();
}

