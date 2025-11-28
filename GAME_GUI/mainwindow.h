#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <QQmlContext>
#include <QStatusBar>
#include <QLabel>
#include "../INCLUDE/JsonFileManager.hpp"
#include "../INCLUDE/SudokuBoard.hpp"

class QMediaPlayer;
class QAudioOutput;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QQuickWidget *qmlWidget;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QPushButton *soundButton;
    QStatusBar *bar;
    QLabel *messageLabel;

    SudokuBoard board;
    GameJsonFileManager fileManager;
};
#endif // MAINWINDOW_H
