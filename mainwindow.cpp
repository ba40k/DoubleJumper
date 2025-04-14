#include "mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)   {
    resize(WIDTH, HEIGHT);
    mainMenuWidget = new MainMenuWidget(this);
    mainMenuWidget->setGeometry(QRect(0, 0, WIDTH, HEIGHT));
    centralWidget = mainMenuWidget;
    setCentralWidget(centralWidget);


}
