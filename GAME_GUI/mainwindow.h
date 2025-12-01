#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <QQmlContext>
#include <QStatusBar>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
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

public slots:
    void updateCellValue(int row, int col, int value);

private:
    void fillBoard(void);
    void showBoard(void);
    void fillShowBoard(void);

    QQuickWidget *qmlWidget;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QPushButton *soundButton;
    QStatusBar *bar;
    QLabel *messageLabel;

    QString filename;

    QVector<QVector<int>> boardQ;
    QVector<QVector<int>> originalBoardQ;  // Store original puzzle state (pre-filled cells)
    SudokuBoard board;
    GameJsonFileManager fileManager;
    bool boardLocked;
};

class saveDialog: public QDialog{
    Q_OBJECT
public:
    saveDialog(QWidget *parent = nullptr);

private:
    QLabel *info;
    QPushButton *no;
    QPushButton *yes;
    QLineEdit *fileName;
signals:
    void yseClicked(const QString& fileName);
    void noClicked(void);
};

class newDialog: public QDialog{
    Q_OBJECT
public:
    newDialog(QWidget *parent = nullptr);

private:
    QLabel *info;
    QPushButton *cancel;
    QPushButton *yes;
    QSpinBox *spinBox;

signals:
    void yseClicked(int);
    void exitClicked(void);
};

class loadDialog: public QDialog{
    Q_OBJECT
public:
    loadDialog(QWidget *parent = nullptr);

private:
    QLabel *info;
    QPushButton *select;
    QPushButton *cancel;
    QLineEdit *fileName;

signals:
    void selectClicked(const QString& fileName);
    void exitClicked(void);
};



#endif // MAINWINDOW_H
