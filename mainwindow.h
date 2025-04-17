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

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
private:

    const int HEIGHT = 850;
    const int WIDTH = 640;
    QWidget *centralWidget;
    Ui::MainWindow *ui;
    MainMenuWidget *mainMenuWidget;
    GameWidget *gameWidget;
    void playButtonClicked();
public:
    MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H