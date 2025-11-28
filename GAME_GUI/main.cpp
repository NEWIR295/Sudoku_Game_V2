#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setFixedSize(750, 620);
    //w.setMinimumSize(750, 620);
    //w.setMaximumSize(750, 620);
    w.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    w.setWindowTitle("Sudoku V2");
    //w.setWindowIcon(QIcon(":/icons/sudoku.png"));
    w.show();
    return a.exec();
}
