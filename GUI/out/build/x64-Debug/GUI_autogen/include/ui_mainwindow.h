/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *P1;
    QGridLayout *gridLayout_6;
    QFrame *frame_3;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_2;
    QWidget *P2;
    QGridLayout *gridLayout_7;
    QWidget *widget;
    QGridLayout *gridLayout_9;
    QFrame *boxesFrame;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_8;
    QTableWidget *tableWidget;
    QWidget *drawingBoard;
    QFrame *chatBoxes;
    QGridLayout *gridLayout_11;
    QFrame *chatFrame;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;
    QFrame *frame;
    QGridLayout *gridLayout_12;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QFrame *answerFrame;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *plainTextEdit_2;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_13;
    QPushButton *pushButton_6;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(926, 699);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                             stop: 0 #001F33, stop: 1 #003366);\n"
""));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(700, 600));
        stackedWidget->setMaximumSize(QSize(1920, 1920));
        P1 = new QWidget();
        P1->setObjectName("P1");
        P1->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                             stop: 0 #001F33, stop: 1 #003366);\n"
""));
        gridLayout_6 = new QGridLayout(P1);
        gridLayout_6->setObjectName("gridLayout_6");
        frame_3 = new QFrame(P1);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8(""));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 6, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 6, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_3, 2, 1, 1, 1);

        label = new QLabel(frame_3);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(700, 700));
        QFont font;
        font.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(16);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font-family: 'Comic Sans MS';\n"
"color: red;\n"
"font-size: 16pt;\n"
"background-color: transparent;\n"
"\n"
""));

        gridLayout_4->addWidget(label, 3, 1, 1, 1);

        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName("frame_4");
        sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy1);
        frame_4->setMaximumSize(QSize(800, 800));
        QFont font1;
        font1.setKerning(true);
        frame_4->setFont(font1);
        frame_4->setAutoFillBackground(false);
        frame_4->setStyleSheet(QString::fromUtf8("background: transparent;"));
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_4->setLineWidth(1);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setObjectName("gridLayout_5");
        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(frame_4);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(50, 70));
        pushButton_3->setMaximumSize(QSize(300, 100));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Consolas")});
        font2.setBold(true);
        pushButton_3->setFont(font2);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #4CAF50, stop: 1 #2196F3);\n"
"    color: white;\n"
"    border: 2px solid #4CAF50;\n"
"    border-radius: 30px;\n"
"    padding: 5px 10px;\n"
"\n"
"	font-family: \"Consolas\";\n"
"    font-size: 36px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FFD700, stop: 1 #FFA500);\n"
"    border: 2px solid #FFD700;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6B6B6B, stop: 1 #8B8B8B);\n"
"    border: 2px solid #808080;\n"
"    color: white;\n"
"}\n"
""));

        gridLayout_5->addWidget(pushButton_3, 3, 0, 1, 1);

        pushButton = new QPushButton(frame_4);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(300, 70));
        pushButton->setMaximumSize(QSize(300, 100));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Consolas")});
        font3.setBold(true);
        font3.setUnderline(false);
        font3.setStrikeOut(false);
        font3.setStyleStrategy(QFont::PreferDefault);
        pushButton->setFont(font3);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #4CAF50, stop: 1 #2196F3);\n"
"    color: white;\n"
"    border: 2px solid #4CAF50;\n"
"    border-radius: 30px;\n"
"    padding: 5px 10px;\n"
"\n"
"	font-family: \"Consolas\";\n"
"    font-size: 36px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FFD700, stop: 1 #FFA500);\n"
"    border: 2px solid #FFD700;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6B6B6B, stop: 1 #8B8B8B);\n"
"    border: 2px solid #808080;\n"
"    color: white;\n"
"}\n"
""));
        pushButton->setAutoRepeat(false);
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);

        gridLayout_5->addWidget(pushButton, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(frame_4);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(50, 70));
        pushButton_2->setMaximumSize(QSize(300, 100));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #4CAF50, stop: 1 #2196F3);\n"
"    color: white;\n"
"    border: 2px solid #4CAF50;\n"
"    border-radius: 30px;\n"
"    padding: 5px 10px;\n"
"\n"
"	font-family: \"Consolas\";\n"
"    font-size: 36px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FFD700, stop: 1 #FFA500);\n"
"    border: 2px solid #FFD700;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6B6B6B, stop: 1 #8B8B8B);\n"
"    border: 2px solid #808080;\n"
"    color: white;\n"
"}\n"
""));

        gridLayout_5->addWidget(pushButton_2, 2, 0, 1, 1);


        gridLayout_4->addWidget(frame_4, 5, 1, 2, 1);


        gridLayout_6->addWidget(frame_3, 0, 0, 1, 1);

        stackedWidget->addWidget(P1);
        P2 = new QWidget();
        P2->setObjectName("P2");
        gridLayout_7 = new QGridLayout(P2);
        gridLayout_7->setObjectName("gridLayout_7");
        widget = new QWidget(P2);
        widget->setObjectName("widget");
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        gridLayout_9 = new QGridLayout(widget);
        gridLayout_9->setObjectName("gridLayout_9");
        boxesFrame = new QFrame(widget);
        boxesFrame->setObjectName("boxesFrame");
        boxesFrame->setEnabled(true);
        sizePolicy.setHeightForWidth(boxesFrame->sizePolicy().hasHeightForWidth());
        boxesFrame->setSizePolicy(sizePolicy);
        boxesFrame->setMinimumSize(QSize(700, 550));
        boxesFrame->setLayoutDirection(Qt::LeftToRight);
        boxesFrame->setStyleSheet(QString::fromUtf8("background: transparent;"));
        boxesFrame->setFrameShape(QFrame::StyledPanel);
        boxesFrame->setFrameShadow(QFrame::Raised);
        gridLayout_10 = new QGridLayout(boxesFrame);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        tableWidget = new QTableWidget(boxesFrame);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy2);
        tableWidget->setMaximumSize(QSize(230, 16777215));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));

        gridLayout_8->addWidget(tableWidget, 0, 0, 1, 1);

        drawingBoard = new QWidget(boxesFrame);
        drawingBoard->setObjectName("drawingBoard");
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(drawingBoard->sizePolicy().hasHeightForWidth());
        drawingBoard->setSizePolicy(sizePolicy3);
        drawingBoard->setCursor(QCursor(Qt::CrossCursor));
        drawingBoard->setStyleSheet(QString::fromUtf8("background-color: white;"));

        gridLayout_8->addWidget(drawingBoard, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_8, 0, 0, 1, 2);

        chatBoxes = new QFrame(boxesFrame);
        chatBoxes->setObjectName("chatBoxes");
        sizePolicy.setHeightForWidth(chatBoxes->sizePolicy().hasHeightForWidth());
        chatBoxes->setSizePolicy(sizePolicy);
        chatBoxes->setMinimumSize(QSize(300, 0));
        chatBoxes->setMaximumSize(QSize(1500, 300));
        chatBoxes->setLayoutDirection(Qt::LeftToRight);
        chatBoxes->setStyleSheet(QString::fromUtf8("background: transparent;"));
        chatBoxes->setFrameShape(QFrame::StyledPanel);
        chatBoxes->setFrameShadow(QFrame::Raised);
        gridLayout_11 = new QGridLayout(chatBoxes);
        gridLayout_11->setObjectName("gridLayout_11");
        chatFrame = new QFrame(chatBoxes);
        chatFrame->setObjectName("chatFrame");
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(chatFrame->sizePolicy().hasHeightForWidth());
        chatFrame->setSizePolicy(sizePolicy4);
        chatFrame->setMinimumSize(QSize(100, 100));
        chatFrame->setMaximumSize(QSize(300, 300));
        chatFrame->setFrameShape(QFrame::StyledPanel);
        chatFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(chatFrame);
        gridLayout->setObjectName("gridLayout");
        lineEdit = new QLineEdit(chatFrame);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy5);
        lineEdit->setMaximumSize(QSize(300, 16777215));
        QFont font4;
        font4.setPointSize(9);
        lineEdit->setFont(font4);
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: white;"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(chatFrame);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy6);
        plainTextEdit->setMaximumSize(QSize(300, 200));
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: white;"));
        plainTextEdit->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);


        gridLayout_11->addWidget(chatFrame, 0, 1, 1, 1);

        frame = new QFrame(chatBoxes);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy7(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy7);
        frame->setMinimumSize(QSize(100, 0));
        frame->setMaximumSize(QSize(200, 300));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_12 = new QGridLayout(frame);
        gridLayout_12->setObjectName("gridLayout_12");
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMaximumSize(QSize(300, 16777215));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop: 0 #FFA500, stop: 1 #FF0000);\n"
"    border: 2px solid #FFA500;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 7px;\n"
"\n"
"	font-family: \"Consolas\";\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FFD700, stop: 1 #FFA500);\n"
"    border: 2px solid #FFA500;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop: 0 #FF4500, stop: 1 #DC143C);\n"
"    border: 2px solid #FFA500;\n"
"    color: white;\n"
"}\n"
""));

        gridLayout_12->addWidget(pushButton_4, 0, 3, 1, 1);

        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMaximumSize(QSize(300, 16777215));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #4CAF50, stop: 1 #2196F3);\n"
"    border: 2px solid #4CAF50;\n"
"	color: white;\n"
"    border-radius: 10px;\n"
"    padding: 7px;\n"
"\n"
"	font-family: \"Consolas\";\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FFD700, stop: 1 #FFA500);\n"
"    border: 2px solid #FFD700;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6B6B6B, stop: 1 #8B8B8B);\n"
"    border: 2px solid #808080;\n"
"    color: white;\n"
"}\n"
""));

        gridLayout_12->addWidget(pushButton_5, 1, 3, 1, 1);


        gridLayout_11->addWidget(frame, 0, 3, 1, 1);

        answerFrame = new QFrame(chatBoxes);
        answerFrame->setObjectName("answerFrame");
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(answerFrame->sizePolicy().hasHeightForWidth());
        answerFrame->setSizePolicy(sizePolicy8);
        answerFrame->setMinimumSize(QSize(100, 100));
        answerFrame->setMaximumSize(QSize(300, 300));
        answerFrame->setFrameShape(QFrame::StyledPanel);
        answerFrame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(answerFrame);
        gridLayout_2->setObjectName("gridLayout_2");
        plainTextEdit_2 = new QPlainTextEdit(answerFrame);
        plainTextEdit_2->setObjectName("plainTextEdit_2");
        plainTextEdit_2->setEnabled(true);
        sizePolicy6.setHeightForWidth(plainTextEdit_2->sizePolicy().hasHeightForWidth());
        plainTextEdit_2->setSizePolicy(sizePolicy6);
        plainTextEdit_2->setMaximumSize(QSize(300, 200));
        plainTextEdit_2->setLayoutDirection(Qt::LeftToRight);
        plainTextEdit_2->setStyleSheet(QString::fromUtf8("background-color: white;"));
        plainTextEdit_2->setReadOnly(true);

        gridLayout_2->addWidget(plainTextEdit_2, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(answerFrame);
        lineEdit_2->setObjectName("lineEdit_2");
        sizePolicy6.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy6);
        lineEdit_2->setMaximumSize(QSize(300, 16777215));
        lineEdit_2->setFont(font4);
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: white;"));

        gridLayout_2->addWidget(lineEdit_2, 1, 0, 1, 1);


        gridLayout_11->addWidget(answerFrame, 0, 2, 1, 1);

        groupBox = new QGroupBox(chatBoxes);
        groupBox->setObjectName("groupBox");
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setMinimumSize(QSize(200, 0));
        groupBox->setMaximumSize(QSize(300, 300));
        gridLayout_13 = new QGridLayout(groupBox);
        gridLayout_13->setObjectName("gridLayout_13");
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        sizePolicy1.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy1);
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: red;"));

        gridLayout_13->addWidget(pushButton_6, 0, 0, 1, 1);


        gridLayout_11->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_10->addWidget(chatBoxes, 1, 0, 1, 1);


        gridLayout_9->addWidget(boxesFrame, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget, 0, 0, 1, 1);

        stackedWidget->addWidget(P2);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 926, 22));
        menubar->setAutoFillBackground(false);
        menubar->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                             stop: 0 #001F33, stop: 1 #003366);\n"
""));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-family:'Consolas','monospace'; font-size:72pt; font-weight:700;\">Gartic</span><span style=\" font-size:72pt; font-weight:700;\"/><span style=\" font-family:'Consolas','monospace'; font-size:72pt; font-weight:700; color:#ff0000;\">.io</span></p></body></html>", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PLAY", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "OPTIONS", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Chat with the others...", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "REPORT", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "LEAVE GAME", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter answer here...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Colors", nullptr));
        pushButton_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
