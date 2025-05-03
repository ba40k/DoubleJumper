#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)   {
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    resize(WIDTH, HEIGHT);
    mainMenuWidget = new MainMenuWidget(this);

    setCentralWidget(mainMenuWidget);
    connect(mainMenuWidget->getPlayButton(),&QPushButton::clicked, this, &MainWindow::playButtonClicked);

}
void MainWindow::playButtonClicked() {
    gameWidget = new GameWidget(this);
    mainMenuWidget->stop();
    gameWidget->run();
    gameWidget->showFullScreen();
    setCentralWidget(gameWidget);
    gameRunning = true;
    ++playClicked;
}
void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (gameRunning) {
        gameWidget->keyPressEvent(event);
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (gameRunning) {
        gameWidget->keyReleaseEvent(event);
    }
}
void MainWindow::backToMenu() {
    gameWidget->stop();
    gameRunning = false;
    mainMenuWidget = new MainMenuWidget(this);
    setCentralWidget(mainMenuWidget);
    connect(mainMenuWidget->getPlayButton(),&QPushButton::clicked, this, &MainWindow::playButtonClicked);
}
