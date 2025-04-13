#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QDialog>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
public:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H