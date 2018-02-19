#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("narob");
    a.setOrganizationName("Dave's Speed Shop");

    MainWindow w;
    w.show();

    return a.exec();
}
