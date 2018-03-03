#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("TAG – a Tool for Analyzing Grains");
    w.show();

    return a.exec();
}
