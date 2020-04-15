#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QPushButton>
#include <QTableView>
#include <QVector>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include "cModel.h"
#include "dialog.h"
#include "proxyModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setRightDockWidget();
    void setLeftDockWidget();
    void setMainDockWidget();

private:
    void init();
    void createMenuBar();
    void createToolBar();
    QWidget* createFirstLayout();
    QWidget* createSecondLayout();
private:
    QMenu *menu1;
    QMenu *menu2;
    QMenu *menu3;
    QAction *quitMenu;
    QAction *exitMenu;
    QAction *activateMenu;
    QAction *quitBar;
    QAction *exitBar;
    QAction *activateBar;
private:
    ProxyModel* proxyModel;
    CustomModel* customModel;
    QTableView* tableView;
    Dialog * dialog;
private:
    QDockWidget *rightDockFirst;
    QDockWidget *rightDockSecond;
    QDockWidget *leftDock;
    QDockWidget *mainDock;
};
#endif // MAINWINDOW_H
