#include "mainwindow.h"
#include "dialog.h"

#include <QApplication>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QStyle>
#include <QLabel>
#include <QFrame>
#include <QRect>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    createMenuBar();
    createToolBar();
    setRightDockWidget();
    setLeftDockWidget();
    setMainDockWidget();
}

void MainWindow::init()
{
    setMinimumSize(500,500);
    dialog = new Dialog;
    proxyModel = new ProxyModel;
    customModel = new CustomModel;
}

void MainWindow::createMenuBar(){

    quitMenu = new QAction("&Quit", this);
    menu1 = menuBar()->addMenu("&Menu1");
    menu1->addAction(quitMenu);
    connect(quitMenu, &QAction::triggered, qApp, QApplication::quit);

    exitMenu = new QAction("&Exit",this);
    menu2 = menuBar()->addMenu("&Menu2");
    menu2->addAction(exitMenu);
    connect(exitMenu, SIGNAL(triggered()),dialog,SLOT(createDialog()));

    activateMenu = new QAction("&Activate Dock Widget",this);
    menu3 = menuBar()->addMenu("&Menu3");
    menu3->addAction(activateMenu);
    activateMenu->setCheckable(true);
}

void MainWindow::createToolBar(){

    QToolBar* toolbar = new QToolBar;
    addToolBar(Qt::BottomToolBarArea,toolbar);
    toolbar->setOrientation(Qt::Horizontal);
    toolbar->setMovable(false);

    quitBar = toolbar->addAction("Quit");
    connect(quitBar, &QAction::triggered, qApp, QApplication::quit);

    exitBar = toolbar->addAction("Exit");
    connect(exitBar, SIGNAL(triggered()),dialog,SLOT(createDialog()));

    activateBar = toolbar->addAction("Activate Dock Widget");
}

void MainWindow::setRightDockWidget(){

    rightDockFirst = new QDockWidget(tr("Layout with QHorizontal and QVertical Layouts!"));
    rightDockFirst->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    rightDockFirst->setWidget(createFirstLayout());
    addDockWidget(Qt::RightDockWidgetArea, rightDockFirst);

    rightDockSecond = new QDockWidget(tr("Layout with QGridLayout Layout!"));
    rightDockSecond->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    rightDockSecond->setWidget(createSecondLayout());
    addDockWidget(Qt::RightDockWidgetArea, rightDockSecond);

    tabifyDockWidget(rightDockFirst,rightDockSecond);

    connect(activateMenu, SIGNAL(toggled(bool)),rightDockFirst,SLOT(raise()));
    connect(activateBar,  SIGNAL(triggered(bool)),rightDockFirst,SLOT(raise()));
}

void MainWindow::setLeftDockWidget()
{
    tableView = new QTableView;
    tableView->setModel(customModel);
    tableView->show();

    leftDock = new QDockWidget("Left Dock Widget");
    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    leftDock->setWidget(tableView);
}
void MainWindow::setMainDockWidget()
{
     mainDock = new QDockWidget("Main Dock Widget");
     QMainWindow::setCentralWidget(mainDock);
     mainDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

     QLabel *filter = new QLabel(tr("&Filter:"));
     QLineEdit *filterInput = new QLineEdit;
     filter->setBuddy(filterInput);
     QWidget *widget = new QWidget;
     QGridLayout *windowLayout = new QGridLayout;

     windowLayout->addWidget(filter,0,0,Qt::AlignRight);
     windowLayout->addWidget(filterInput,0,1);

     tableView = new QTableView;
     QHeaderView* horHeader = tableView->horizontalHeader();
     horHeader->setDefaultSectionSize(200);
     tableView->setModel(customModel);
     proxyModel->setSourceModel(customModel);
     tableView->setModel(proxyModel);
     tableView->setSortingEnabled(true);

     QTableView  *fTableView = new QTableView;
     ProxyModel  *proxyMod   = new ProxyModel;
     QHeaderView *hHeader = fTableView->horizontalHeader();

     hHeader->setDefaultSectionSize(200);
     proxyMod->setSourceModel(customModel);
     fTableView->setModel(proxyMod);
     fTableView->setSortingEnabled(true);

     connect(filterInput, SIGNAL(textChanged(const QString&)),proxyMod, SLOT(filterAccepted(const QString&)));
     fTableView->sortByColumn(0);

     windowLayout->addWidget(tableView,1,0);
     windowLayout->addWidget(fTableView,1,1);
     widget->setLayout(windowLayout);

     mainDock->setWidget(widget);
     tableView->show();
     fTableView->show();
}

QWidget* MainWindow::createFirstLayout(){
    QWidget* widget = new QWidget;

    QPushButton *buttonA = new QPushButton("A");
    QPushButton *buttonB = new QPushButton("B");
    QPushButton *buttonC = new QPushButton("C");
    QPushButton *buttonD = new QPushButton("D");
    QPushButton *buttonE = new QPushButton("E");
    QPushButton *buttonF = new QPushButton("F");

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(buttonA);
    hlayout->addWidget(buttonB);
    hlayout->addWidget(buttonC);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addWidget(buttonD);
    vlayout->addWidget(buttonE);
    vlayout->addWidget(buttonF);

    widget->setLayout(vlayout);
    widget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Maximum);
    widget->show();

    return widget;
}

QWidget* MainWindow::createSecondLayout(){
    QWidget* widget = new QWidget;

    QPushButton *buttonA = new QPushButton("A");
    QPushButton *buttonB = new QPushButton("B");
    QPushButton *buttonC = new QPushButton("C");
    QPushButton *buttonD = new QPushButton("D");
    QPushButton *buttonE = new QPushButton("E");
    QPushButton *buttonF = new QPushButton("F");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(buttonA,0,0);
    layout->addWidget(buttonB,0,1);
    layout->addWidget(buttonC,0,2);
    layout->addWidget(buttonD,1,0,1,3);
    layout->addWidget(buttonE,2,0,2,3);
    layout->addWidget(buttonF,3,0,3,3);
    widget->setLayout(layout);

    widget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    widget->show();

    return widget;

}
MainWindow::~MainWindow()
{
}

