#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QDialog>
#include <QMenu>
#include "MainMenuWidget.h"
#include "gameVisualisation/gameWidget.h"
#include "RecordsWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    int playClicked = 0;
public:
    bool soundOn = true;
    bool visibleScoreMarkers = true;

    RecordDatabase *records;
    void backToMenu();
    const int HEIGHT = 850;
    const int WIDTH = 640;
    QWidget *centralWidget;
    Ui::MainWindow *ui;
    MainMenuWidget *mainMenuWidget;
    GameWidget *gameWidget;
    void playButtonClicked();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool gameRunning;

    MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H