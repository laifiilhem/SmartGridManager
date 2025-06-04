#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Utilisez QApplication pour les apps GUI
    MainWindow w;
    w.show();
    return a.exec();
}