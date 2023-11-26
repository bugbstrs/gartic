#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Main menu buttons
    void on_playButton_released();
    void on_quitButton_released();
    void on_redColorButton_released();
    void on_goToSignUpButton_released();

    //Drawing scene buttons
    void on_leaveGameButton_released();

    //Stats scene
    void on_statsButton_released();
    void on_backToMenuButton_released();

    //SignUp scene
private:
    std::unique_ptr<Ui::MainWindow> ui = std::make_unique<Ui::MainWindow>();
    bool isUserLoggedIn;
};
#endif // MAINWINDOW_H