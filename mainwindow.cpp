#include "mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)   {
    resize(WIDTH, HEIGHT);
    mainMenuWidget = new MainMenuWidget(this);
    gameWidget = new GameWidget(this);
    centralWidget = mainMenuWidget;
    setCentralWidget(centralWidget);

    connect(mainMenuWidget->getPlayButton(),&QPushButton::clicked, this, &MainWindow::playButtonClicked);

}
void MainWindow::playButtonClicked() {
    mainMenuWidget->stop();
    setCentralWidget(gameWidget);
}
