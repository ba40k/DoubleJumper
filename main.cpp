#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include <QLoggingCategory>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
