#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent)   {
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    resize(WIDTH, HEIGHT);
    mainMenuWidget = new MainMenuWidget(this);
    gameWidget = new GameWidget(this);

    centralWidget = mainMenuWidget;
    setCentralWidget(centralWidget);

    connect(mainMenuWidget->getPlayButton(),&QPushButton::clicked, this, &MainWindow::playButtonClicked);

}
void MainWindow::playButtonClicked() {
    mainMenuWidget->stop();
    gameWidget->run();
    setCentralWidget(gameWidget);
    gameRunning = true;

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