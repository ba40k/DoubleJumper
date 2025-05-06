#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)   {
    if (!inites) {
        currentTheme = new DefaultTheme();
        themes = new QVector<Theme *>();
        *themes = {new DefaultTheme, new HaloweenTheme, new UnderwaterTheme, new JungleTheme};
        inites = true;
    }
    records = new RecordDatabase;
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    resize(WIDTH, HEIGHT);
    mainMenuWidget = new MainMenuWidget(this);
    setCentralWidget(mainMenuWidget);
    connect(mainMenuWidget->getPlayButton(),&QPushButton::clicked, this, &MainWindow::playButtonClicked);

}
void MainWindow::playButtonClicked() {
    gameWidget = new GameWidget(visibleScoreMarkers,this);
    gameWidget->setTheme(currentTheme);
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
    mainMenuWidget->setTheme(currentTheme);
    setCentralWidget(mainMenuWidget);
    connect(mainMenuWidget->getPlayButton(),&QPushButton::clicked, this, &MainWindow::playButtonClicked);
}
