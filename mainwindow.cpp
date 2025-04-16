#include "mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)   {
    resize(WIDTH, HEIGHT);
    mainMenuWidget = new MainMenuWidget(this);
    centralWidget = mainMenuWidget;
    setCentralWidget(centralWidget);


}
