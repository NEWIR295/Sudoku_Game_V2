#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QString>
#include <QMovie>
#include <QPushButton>
#include <QSize>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDesktopServices>

#include "../INCLUDE/SudokuBoard.hpp"
#include "../INCLUDE/SudokuGenerator.hpp"
#include "../INCLUDE/SudokuSolver.hpp"
#include "../INCLUDE/JsonFileManager.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , qmlWidget(nullptr)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , soundButton(nullptr)
{

    this -> setFixedSize(750, 620);
    this -> setWindowIcon(QIcon(":/icons/sudoku.png"));

    // Example Sudoku board
    QList<QList<int>> board = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };

    QString statusMessage = "Ready";

    /* music */
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/music/music.mp3"));
    audioOutput->setVolume(0.4);
    player->setLoops(QMediaPlayer::Infinite);
    player->play();

    auto *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);

    layout->setContentsMargins(10, 0, 10, 10);
    layout->setSpacing(0);

    /* sound button */
    soundButton = new QPushButton("Volume", container);
    soundButton->setCheckable(true);
    soundButton->setChecked(false);
    soundButton->setIcon(QIcon(":/icons/volume.png"));
    soundButton->setIconSize(QSize(24, 24));

    QHBoxLayout *topRow = new QHBoxLayout;
    topRow->addStretch();
    topRow->addWidget(soundButton, 0, Qt::AlignCenter | Qt::AlignLeft );
    layout->addLayout(topRow);
    layout->addSpacing(5);

    qmlWidget = new QQuickWidget(container);
    qmlWidget->setFixedSize(500, 500);
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Pass C++ board to QML
    qmlWidget->rootContext()->setContextProperty("sudokuBoard", QVariant::fromValue(board));

    // Load QML
    qmlWidget->setSource(QUrl("qrc:/qml/sudokuBoard.qml"));

    // Adjust main window
    QHBoxLayout *contentRow = new QHBoxLayout;
    contentRow->addWidget(qmlWidget, 0, Qt::AlignTop);

    /* Personal Info Data */
    QVBoxLayout *personalInfo = new QVBoxLayout;
    personalInfo->setSpacing(12);
    personalInfo->addStretch();

    QPushButton *linkedInButton = new QPushButton("Newir LinkedIn Account", container);
    linkedInButton -> setIcon(QIcon(":/icons/linkedin.png"));
    QPushButton *gitHubButton = new QPushButton("Newir GitHub Account", container);
    gitHubButton -> setIcon(QIcon(":/icons/github.png"));

    personalInfo->addWidget(linkedInButton, 0, Qt::AlignHCenter);
    personalInfo->addWidget(gitHubButton, 0, Qt::AlignHCenter);
    personalInfo->addStretch();

    QLabel *catGif = new QLabel(container);
    QMovie *catMovie = new QMovie(":/gif/yes.gif", QByteArray(), catGif);
    catGif->setMovie(catMovie);
    catMovie->start();

    QVBoxLayout *sideColumn = new QVBoxLayout;
    sideColumn->addStretch();
    sideColumn->addLayout(personalInfo);
    sideColumn->addStretch();
    sideColumn->addWidget(catGif, 0, Qt::AlignRight | Qt::AlignBottom);

    contentRow->addLayout(sideColumn);
    layout->addLayout(contentRow);
    layout->addStretch();

    QAction *newAction = new QAction("New");
    newAction -> setIcon(QIcon(":/icons/new.png"));
    newAction -> setStatusTip("Generate New Game");
    connect(newAction, &QAction::triggered, this,[](){
        //generate new game function
    });

    QAction *saveAction = new QAction("Save");
    saveAction -> setIcon(QIcon(":/icons/save.png"));
    saveAction -> setStatusTip("Save Game");
    connect(saveAction, &QAction::triggered, this,[](){
        //save game function
    });

    QAction *solveAction = new QAction("Solve");
    solveAction -> setStatusTip("Generate a Solution");
    solveAction -> setIcon(QIcon(":/icons/solve.png"));
    connect(solveAction, &QAction::triggered, this,[](){
        //generate solve game function
    });

    QAction *loadAction = new QAction("Load");
    loadAction -> setIcon(QIcon(":/icons/load.png"));
    loadAction -> setStatusTip("Load Game");
    connect(loadAction, &QAction::triggered, this,[](){
        //generate load game function
    });

    QToolBar *toolBar = addToolBar("Game ToolBar");
    toolBar -> addSeparator();
    toolBar -> addAction(newAction);
    toolBar -> addSeparator();
    toolBar -> addAction(saveAction);
    toolBar -> addSeparator();
    toolBar -> addAction(solveAction);
    toolBar -> addSeparator();
    toolBar -> addAction(loadAction);
    toolBar -> addSeparator();

    /* status */
    bar = statusBar();
    QLabel *statusLabel = new QLabel(tr("Game Status: "), bar);
    messageLabel = new QLabel(statusMessage, bar);
    bar->addWidget(statusLabel);
    bar->addWidget(messageLabel, 1);

    connect(soundButton, &QPushButton::toggled, this, [this](bool muted){
        audioOutput->setMuted(muted);
        soundButton->setIcon(QIcon(muted ? ":/icons/mute.png"
                                         : ":/icons/volume.png"));
        soundButton->setText(muted ? "Muted" : "Volume");
        muted? messageLabel -> setText("Sound Muted") : messageLabel -> setText("Sound unMuted");
        bar->addWidget(messageLabel, 1);
    });

    connect(linkedInButton, &QPushButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.linkedin.com/in/mohamed-newir-a8a572182"));
    });

    connect(gitHubButton, &QPushButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://github.com/NEWIR295"));
    });

    setCentralWidget(container);

}

MainWindow::~MainWindow()
{
}
