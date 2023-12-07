#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcursor.h>

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
    void OnLeaveGameButtonReleased();
    void OnEraserButtonReleased();
    void OnPencilEnabled();
    void OnFillEnabled();

    //Stats scene
    void OnBackToMenuButtonReleased();

    //Sign Up scene
    void OnGoToLogInFromSignUpButtonReleased();

    //Log In scene
    void OnGoToSignUpFromLogInButtonReleased();
private:
    /*std::unique_ptr<Ui::MainWindow> ui = std::make_unique<Ui::MainWindow>();*/
    Ui::MainWindow* ui;
    bool isUserLoggedIn;
    QCursor eraserCursor;
    QCursor fillCursor;
};
#endif // MAINWINDOW_H