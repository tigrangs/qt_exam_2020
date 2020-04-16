#pragma once

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QMenuBar>
#include <QTableView>
#include <QLayout>
#include <QDockWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
#include <QAction>
#include <QMessageBox>

#include "mymodel.h"
#include "myproxymodel.h"

class MainWindow : public QMainWindow{
     Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
private:
    bool first_is_visible = false;
private:
    QDockWidget* right_widget_1 = nullptr;
    QDockWidget* right_widget_2 = nullptr;
    QDockWidget* left_widget = nullptr;
private:
    QToolBar* toolbar = nullptr;
private:
    MyModel* sourceModel = nullptr;
    QTableView* sourceView = nullptr;
    MyProxyModel* proxyModel = nullptr;
    QTableView* proxyView = nullptr;
private:
    QVBoxLayout* vboxlayout = nullptr;
    QGridLayout* gridlayout = nullptr;
    QGridLayout* viewLayout = nullptr;
private:
    void createMenubar();
    void createToolbar();
    void createModel_View();
    void createDockWidgets();
    void createCentralwidget();
    void createHVboxlayout();
    void createGridlayout();
public slots:
    void change_selection();
};

