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
    void OnPlayButtonReleased();
    void OnQuitButtonReleased();
    void OnStatsButtonReleased();
    void OnGoToLogInButtonReleased();
    void OnGoToSignUpButtonReleased();

    //Drawing scene
    void OnRedColorButtonReleased();
    void OnLeaveGameButtonReleased();

    //Stats scene
    void OnBackToMenuButtonReleased();

    //SignUp scene
private:
    std::unique_ptr<Ui::MainWindow> ui = std::make_unique<Ui::MainWindow>();
    bool isUserLoggedIn;
};
#endif // MAINWINDOW_H