#include "mainWindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){

    this->setMinimumWidth(900);
    this->setMinimumHeight(700);
    viewLayout = new QGridLayout;

    createHVboxlayout();
    createGridlayout();

    createToolbar();
    createMenubar();
    createModel_View();
    createCentralwidget();
    createDockWidgets();
}

void MainWindow::createToolbar()
{
    toolbar = new QToolBar(this);
    this->addToolBar(Qt::ToolBarArea::BottomToolBarArea, toolbar);
    toolbar->setMovable(false);
    QAction* act1 = toolbar->addAction("Quit");
    QAction* act2 = toolbar->addAction("Safe Quit");
    QAction* act3 = toolbar->addAction("Selection change");
    act2->setCheckable(true);
    act2->setObjectName("safe quit action");
    act3->setObjectName("change selection action");

    connect(act1, &QAction::triggered, [this,act2](){
        if(act2->isChecked()){
            QMessageBox* b = new QMessageBox(this);
            b->setIcon(QMessageBox::Warning);
            b->setText("Discard changes and close the application?");
            b->setWindowTitle("Warning");
            b->setAttribute(Qt::WA_DeleteOnClose, true);
            QPushButton* cancelbutton = b->addButton("Cancel", QMessageBox::RejectRole);
            QPushButton* okbutton = b->addButton("Ok", QMessageBox::AcceptRole);
            b->show();

            connect(cancelbutton, &QPushButton::clicked, [b]() {
                b->close();
            });
            connect(okbutton, &QPushButton::clicked, [this,b]() {
                b->close();
                this->close();
            });
        }else{
            this->close();
        }
    });

    act3->setCheckable(true);
    act3->setChecked(true);
    QObject::connect(act3, SIGNAL(changed()), this, SLOT(change_selection()));
}

void MainWindow::createMenubar()
{
    QMenuBar* menubar = new QMenuBar;
    this->setMenuBar(menubar);


    QMenu* menu2 = new QMenu("Menu2", menubar);
    QAction* act2 = this->toolbar->findChild<QAction*>("safe quit action");
    menu2->addAction(act2);


    QMenu* menu1 = new QMenu("Menu1", menubar);
    QAction* act1 = menu1->addAction("Quit");

    connect(act1, &QAction::triggered, [this,act2](){
        if(act2->isChecked()){
            QMessageBox* b = new QMessageBox(this);
            b->setIcon(QMessageBox::Warning);
            b->setText("Discard changes and close the application?");
            b->setWindowTitle("Warning");
            b->setAttribute(Qt::WA_DeleteOnClose, true);
            QPushButton* cancelbutton = b->addButton("Cancel", QMessageBox::RejectRole);
            QPushButton* okbutton = b->addButton("Ok", QMessageBox::AcceptRole);
            b->show();

            connect(cancelbutton, &QPushButton::clicked, [b]() {
                b->close();
            });
            connect(okbutton, &QPushButton::clicked, [this,b]() {
                b->close();
                this->close();
            });
        }else{
            this->close();
        }
    });

    QMenu* menu3 = new QMenu("Menu3", menubar);
    QAction* act3 = this->toolbar->findChild<QAction*>("change selection action");
    menu3->addAction(act3);

    menubar->addMenu(menu1);
    menubar->addMenu(menu2);
    menubar->addMenu(menu3);
}

void MainWindow::createModel_View()
{
    sourceModel = new MyModel;

    sourceView = new  QTableView;
    sourceView->setModel(sourceModel);
    sourceView->setAlternatingRowColors(true);
    sourceView->setColumnWidth(0, 200);
    sourceView->show();

    proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(sourceModel);

    proxyView = new QTableView;
    proxyView->setModel(proxyModel);
    proxyView->sortByColumn(1, Qt::AscendingOrder);
    proxyView->setSortingEnabled(true);
    proxyView->setColumnWidth(0, 200);
}

void MainWindow::createDockWidgets()
{
    left_widget = new QDockWidget("Left widget", this);
    right_widget_1 = new QDockWidget( "HVBoxLayout dockWidget", this);
    right_widget_2 = new QDockWidget( "Gridlayout dockWidget", this);

    left_widget->setAllowedAreas(Qt::LeftDockWidgetArea);
    left_widget->setWidget(sourceView);

    right_widget_1->setFeatures(QDockWidget::NoDockWidgetFeatures);
    right_widget_2->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QWidget* layoutwidget1 = new QWidget;
    QWidget* layoutwidget2 = new QWidget;
    layoutwidget1->setLayout(vboxlayout);
    layoutwidget2->setLayout(gridlayout);
    layoutwidget1->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    layoutwidget2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    addDockWidget(Qt::LeftDockWidgetArea, left_widget);
    addDockWidget(Qt::RightDockWidgetArea, right_widget_1);
    addDockWidget(Qt::RightDockWidgetArea, right_widget_2);

    right_widget_1->setWidget(layoutwidget1);
    right_widget_2->setWidget(layoutwidget2);
    tabifyDockWidget(right_widget_2,right_widget_1);

    QObject::connect(right_widget_1, SIGNAL(visibilityChanged(bool)), this, SLOT(visibilityChangeReceived(bool )));
}

void MainWindow::createCentralwidget()
{
    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setLayout(viewLayout);
    QLabel* title = new QLabel("Main widget", this);
    QLabel* filter = new QLabel("Filter", this);
    title->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    filter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLineEdit* lineedit = new QLineEdit;
    lineedit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QObject::connect(lineedit, SIGNAL(textChanged(QString)), proxyModel, SLOT(setFilterFixedString(QString)));

    viewLayout->addWidget(title, 0,0);
    viewLayout->addWidget(filter, 1,6, Qt::AlignRight);
    viewLayout->addWidget(lineedit, 1,7,Qt::AlignRight);
    viewLayout->addWidget(proxyView, 2,0, 2,8);
    proxyView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainWindow::createHVboxlayout()
{
    vboxlayout = new QVBoxLayout;

    QHBoxLayout* abclayout = new QHBoxLayout;
    abclayout->addWidget(new QPushButton("A"));
    abclayout->addWidget(new QPushButton("B"));
    abclayout->addWidget(new QPushButton("C"));

    vboxlayout->addLayout(abclayout);
    vboxlayout->addWidget(new QPushButton("D"));
    vboxlayout->addWidget(new QPushButton("E"));
    vboxlayout->addWidget(new QPushButton("F"));
}

void MainWindow::createGridlayout()
{
    gridlayout = new QGridLayout;

    gridlayout->addWidget(new QPushButton("A"),0,0);
    gridlayout->addWidget(new QPushButton("B"),0,1);
    gridlayout->addWidget(new QPushButton("C"),0,2);
    gridlayout->addWidget(new QPushButton("D"),1,0,1,3);
    gridlayout->addWidget(new QPushButton("E"),2,0,1,3);
    gridlayout->addWidget(new QPushButton("F"),3,0,1,3);
}

void MainWindow::change_selection()
{
    QAction* act3 = this->toolbar->findChild<QAction*>("change selection action");
    right_widget_1->blockSignals(true);
    act3->isChecked() ? right_widget_2->raise() : right_widget_1->raise();
    right_widget_1->blockSignals(false);
}

void MainWindow::visibilityChangeReceived(bool)
{
    QAction* act3 = this->toolbar->findChild<QAction*>("change selection action");
    act3->blockSignals(true);
    act3->setChecked(!act3->isChecked());
    act3->blockSignals(false);
}

