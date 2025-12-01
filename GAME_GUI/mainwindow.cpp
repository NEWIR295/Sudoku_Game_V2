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
#include <QVector>
#include <vector>
#include <QScrollArea>
#include <filesystem>

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
    , boardLocked(false)
{

    this -> setFixedSize(750, 620);
    this -> setWindowIcon(QIcon(":/icons/sudoku.png"));

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

    // show board
    fileManager.readJsonFile(board.getBoardData());
    this -> fillShowBoard();

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

    /* status */
    bar = statusBar();
    QLabel *statusLabel = new QLabel(tr("Game Status: "), bar);
    messageLabel = new QLabel(statusMessage, bar);
    bar->addWidget(statusLabel);
    bar->addWidget(messageLabel, 1);


    QAction *newAction = new QAction("New");
    newAction -> setIcon(QIcon(":/icons/new.png"));
    newAction -> setStatusTip("Generate New Game");
    connect(newAction, &QAction::triggered, this,[this](){

        //generate new game function
        newDialog newGame(this);
        int level;
        connect(&newGame, &newDialog::yseClicked, [this, &level](const int value){
            level = value;
        });
        newGame.setModal(true);

        //save game function
        if(newGame.exec() == QDialog::Accepted){
            boardLocked = false;
            SudokuGenerator::generatePuzzle(board, level);

            messageLabel -> setText("New Game");
            this -> fillShowBoard();
        }

    });

    QAction *saveAction = new QAction("Save");
    saveAction -> setIcon(QIcon(":/icons/save.png"));
    saveAction -> setStatusTip("Save Game");
    connect(saveAction, &QAction::triggered, this,[this](){

        saveDialog save(this);

        //save.adjustSize();
        //QPoint centerPos = this->frameGeometry().center() - save.frameGeometry().center();
        //save.move(centerPos);

        connect(&save, &saveDialog::yseClicked, this, [this](const QString &filename){
            this -> filename = filename;
        });

        save.setModal(true);

        //save game function
        if(save.exec() == QDialog::Accepted){
            fileManager.changeFile(this -> filename.toStdString());
            fileManager.writeJsonFile(board.getBoardData());
            messageLabel -> setText("Game Saved");
        }
    });

    QAction *solveAction = new QAction("Solve");
    solveAction -> setStatusTip("Generate a Solution");
    solveAction -> setIcon(QIcon(":/icons/solve.png"));
    connect(solveAction, &QAction::triggered, this,[this](){
        //generate solve game function
        if(SudokuSolver::sudokuSolver(board)){
            boardLocked = true;
            messageLabel -> setText("Solution generated");
            this -> fillShowBoard();

            //new game or exit

            //generate new game function
            newDialog newGame(this);
            int level;
            connect(&newGame, &newDialog::yseClicked, [this, &level](const int value){
                level = value;
            });

            // connect(&newGame,&newDialog::exitClicked, this, &QDialog::close);

            newGame.setModal(true);

            //save game function
            if(newGame.exec() == QDialog::Accepted){
                boardLocked = false;
                SudokuGenerator::generatePuzzle(board, level);

                messageLabel -> setText("New Game");
                this -> fillShowBoard();
            }

        } else {
            messageLabel -> setText("Unable to solve current board");
        }
    });

    QAction *loadAction = new QAction("Load");
    loadAction -> setIcon(QIcon(":/icons/load.png"));
    loadAction -> setStatusTip("Load Game");
    connect(loadAction, &QAction::triggered, this, [this](){
        //generate load game function

        loadDialog load(this);

        //save.adjustSize();
        //QPoint centerPos = this->frameGeometry().center() - save.frameGeometry().center();
        //save.move(centerPos);

        connect(&load, &loadDialog::selectClicked, this, [this](const QString &filename){
            this -> filename = filename;
        });

        load.setModal(true);

        //load game function
        if(load.exec() == QDialog::Accepted){
            boardLocked = false;
            fileManager.changeFile(this -> filename.toStdString());
            fileManager.readJsonFile(board.getBoardData());
            messageLabel -> setText("Game Loaded");
            this -> fillShowBoard();
        }
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

void MainWindow::fillShowBoard(void){
    this -> fillBoard();
    this -> showBoard();
}

void MainWindow::fillBoard(void){
    boardQ.clear(); // ensure UI always reflects the latest board only
    originalBoardQ.clear(); // Store original puzzle state
    const std::vector<std::vector<int>> &boardVector = board.getBoardData();
    for (const auto &row : boardVector) {
        boardQ.append(QVector<int>(row.begin(), row.end()));
        originalBoardQ.append(QVector<int>(row.begin(), row.end())); // Save original state
    }
}

void MainWindow::showBoard(void){
    // Pass C++ board to QML
    qmlWidget->rootContext()->setContextProperty("sudokuBoard", QVariant::fromValue(boardQ));
    qmlWidget->rootContext()->setContextProperty("sudokuBoardLocked", boardLocked);
    qmlWidget->rootContext()->setContextProperty("mainWindow", this);

    // Load QML
    qmlWidget->setSource(QUrl("qrc:/qml/sudokuBoard.qml"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateCellValue(int row, int col, int value)
{
    // Check if this cell was pre-filled in the original puzzle
    if (originalBoardQ[row][col] != 0) {
        messageLabel->setText(QString("Cell [%1,%2] is pre-filled and cannot be edited").arg(row).arg(col));
        // Revert the QML board to match the actual board
        boardQ[row][col] = board.getCell(row, col);
        qmlWidget->rootContext()->setContextProperty("sudokuBoard", QVariant::fromValue(boardQ));
        return; // Exit early - don't allow editing pre-filled cells
    }

    // Update the C++ board
    if (board.setCell(row, col, value)) {
        // Update the QML board
        boardQ[row][col] = value;
        // Refresh the QML Board
        qmlWidget->rootContext()->setContextProperty("sudokuBoard", QVariant::fromValue(boardQ));
        
        // Update status message
        messageLabel->setText(QString("Cell [%1,%2] = %3").arg(row).arg(col).arg(value));
        
        // Check if puzzle is complete
        if (board.checkComplete()) {
            messageLabel->setText("Congratulations! Puzzle solved!");

            //generate new game function
            newDialog newGame(this);
            int level;
            connect(&newGame, &newDialog::yseClicked, [this, &level](const int value){
                level = value;
            });
            newGame.setModal(true);

            //save game function
            if(newGame.exec() == QDialog::Accepted){
                boardLocked = false;
                SudokuGenerator::generatePuzzle(board, level);

                messageLabel -> setText("New Game");
                this -> fillShowBoard();
            }

        }
    } else {
        // Invalid move
        messageLabel->setText(QString("Invalid value %1 at [%2,%3]").arg(value).arg(row).arg(col));
        // Revert the QML board to match the actual board
        boardQ[row][col] = board.getCell(row, col);
        qmlWidget->rootContext()->setContextProperty("sudokuBoard", QVariant::fromValue(boardQ));
    }
}

saveDialog::saveDialog(QWidget *parent) : QDialog(parent){

    this->setWindowTitle("Saving");
    this->setFixedSize(320, 150);
    this->setWindowIcon(QIcon(":/icons/save.png"));

    this->info = new QLabel("Do you really want to save the game?", this);
    this->info->setAlignment(Qt::AlignCenter);

    this->fileName = new QLineEdit(this);
    this->fileName->setPlaceholderText("Enter new game name");
    this->fileName->setAlignment(Qt::AlignCenter);

    this->yes = new QPushButton("Yes", this);
    this->no  = new QPushButton("No", this);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(yes);
    hLayout->addSpacing(10);
    hLayout->addWidget(no);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(info);
    vLayout->addSpacing(10);
    vLayout->addWidget(fileName);
    vLayout->addSpacing(15);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);


    connect(yes, &QPushButton::clicked, this, [this](){
        emit yseClicked(this -> fileName -> text());
        accept();
    });

    connect(no, &QPushButton::clicked, this, [this](){
        emit noClicked();
        reject();
    });
}

newDialog::newDialog(QWidget *parent) : QDialog(parent){

    this->setWindowTitle("New Game");
    this->setFixedSize(320, 150);
    this->setWindowIcon(QIcon(":/icons/new.png"));

    this->info = new QLabel("Do you really want new game?", this);
    this->info->setAlignment(Qt::AlignCenter);

    this -> spinBox = new QSpinBox(this);
    this -> spinBox -> setAlignment(Qt::AlignCenter);
    this -> spinBox -> setRange(1,4);
    this -> spinBox -> setValue(1);
    this -> spinBox -> setPrefix("Level: ");

    this-> yes = new QPushButton("Yes", this);
    this-> cancel  = new QPushButton("Cancel", this);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(yes);
    hLayout->addSpacing(10);
    hLayout->addWidget(cancel);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(info);
    vLayout->addSpacing(10);
    vLayout->addWidget(spinBox);
    vLayout->addSpacing(15);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);


    connect(yes, &QPushButton::clicked, this, [this](){
        emit yseClicked(spinBox->value());
        accept();
    });

    connect(cancel, &QPushButton::clicked, this, [this](){
        emit exitClicked();
        reject();
    });
}

loadDialog::loadDialog(QWidget *parent) : QDialog(parent){

    // ---------------- Window setup ----------------
    setWindowTitle("Load Game");
    setFixedSize(320, 250);  // slightly taller for file list
    setWindowIcon(QIcon(":/icons/load.png"));

    // ---------------- Info label ----------------
    info = new QLabel("Do you really want to load existing game?", this);
    info->setAlignment(Qt::AlignCenter);

    // ---------------- File list (scrollable) ----------------
    QWidget *filesContainer = new QWidget(this);        // container for labels
    QVBoxLayout *filesLayout = new QVBoxLayout(filesContainer);

    for (const auto &file : std::filesystem::directory_iterator("../Puzzle/"))
    {
        if (file.path().extension() == ".json")
        {
            auto *label = new QLabel(QString::fromStdString(file.path().filename().stem().string()), this);
            label->setAlignment(Qt::AlignCenter);
            filesLayout->addWidget(label);
        }
    }

    filesLayout->addStretch();  // push files to top

    QScrollArea *scrollArea = new QScrollArea(this);   // optional scroll if many files
    scrollArea->setWidget(filesContainer);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedHeight(80);  // adjust height as needed
    scrollArea->setFrameShape(QFrame::NoFrame);

    // ---------------- File name input ----------------
    fileName = new QLineEdit(this);
    fileName->setPlaceholderText("Enter existing game name");
    fileName->setAlignment(Qt::AlignCenter);

    // ---------------- Buttons ----------------
    select = new QPushButton("Yes", this);
    cancel = new QPushButton("Cancel", this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(select);
    buttonsLayout->addSpacing(10);
    buttonsLayout->addWidget(cancel);
    buttonsLayout->addStretch();

    // ---------------- Main layout ----------------
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(info);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(scrollArea);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(fileName);
    mainLayout->addSpacing(15);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    // ---------------- Signals ----------------
    connect(select, &QPushButton::clicked, this, [this]() {
        emit selectClicked(fileName->text());
        accept();
    });

    connect(cancel, &QPushButton::clicked, this, [this]() {
        emit exitClicked();
        reject();
    });
}


