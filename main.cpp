#include "mainwindow.h"
#include <QApplication>
#include <ctime>

MainWindow *pMain;

int main(int argc, char *argv[])
{
    srand(time(NULL)); //for random integers
    QApplication a(argc, argv);
    MainWindow mainWin;
    pMain = &mainWin;
    mainWin.show(); //show the window
    return a.exec();
}
