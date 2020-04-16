#include "mainwindow.h"
#include <QtWidgets/QToolBar>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include<QDockWidget>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QTableView>
#include<QLabel>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QPushButton>
void MainWindow::centralWidget()
{
	

     main_widget = new QWidget();
     setCentralWidget(main_widget);
     
     QLabel *filter = new QLabel(tr("&Filter:"));
     QLineEdit *filterInput = new QLineEdit;
     filter->setBuddy(filterInput);

     QGridLayout *windowLayout = new QGridLayout; 
     windowLayout->addWidget(filter,0,0,Qt::AlignRight);
     windowLayout->addWidget(filterInput,0,1,Qt::AlignLeft);

     QTableView* tableView = new QTableView();
     MyModel* mod = model_dock_widget->get_model();
     tableView->setModel(mod);
     proxy = new MyProxy();
     proxy->setSourceModel(mod);
     tableView->setModel(proxy);
     tableView->setSortingEnabled(true);
     connect(filterInput, SIGNAL(textChanged(const QString&)),proxy, SLOT(filterAccepted(const QString&)));
     tableView->sortByColumn(0);
     windowLayout->addWidget(tableView,1,0);
     main_widget->setLayout(windowLayout);
     

}
void MainWindow::createMenus()
{

  
  menu_vec[0] = menuBar()->addMenu("&Menu1");
  menu_vec[1] = menuBar()->addMenu("&Menu2");
  menu_vec[2] = menuBar()->addMenu("&Menu3");
  
  menuBar()->setNativeMenuBar(false);

  menu_quit = new QAction("&Quit", this);
  menu_check_quit = new QAction("&CheckableQuit", this);
  menu_dock = new QAction("Activate",this);

  menu_dock->setCheckable(true);
  menu_dock->setChecked(false);  
  menu_check_quit->setCheckable(true);
  menu_check_quit->setChecked(false);

  dialog = new MyDialog(menu_check_quit,this);

  menu_vec[0]->addAction(menu_quit);
  menu_vec[1]->addAction(menu_check_quit);
  menu_vec[2]->addAction(menu_dock);

  connect(menu_quit, &QAction::triggered, qApp, &QApplication::quit);
  connect(menu_check_quit, &QAction::toggled, dialog, &MyDialog::open);


}

void MainWindow::createToolBars()
{

 QPixmap quit_pix("cat.png"),exit_pix("cat.png"),activate_pix("cat.png");
 toolbar = new QToolBar("main_toolbar");
 addToolBar(Qt::BottomToolBarArea,toolbar);

 toolbar_quit = toolbar->addAction(QIcon(quit_pix), "Quit Application");
 toolbar_exit  = toolbar->addAction(QIcon(exit_pix),
      "Exit Application");
 toolbar_dock = toolbar->addAction(QIcon(activate_pix), "Activating dockwidget");

 toolbar->addSeparator();


  connect(toolbar_quit, &QAction::triggered, qApp, &QApplication::quit);
  connect(toolbar_exit, &QAction::triggered, dialog, &MyDialog::open);


}

void MainWindow::ShowDoc(bool state)
{
	if (state == 0)
	{
		dock_vec[1]->raise();
	}
	else
	{
		dock_vec[0]->raise();
	}

}

void MainWindow::createLeftDockWindow()
{
    
    model_dock_widget  = new MyModelDockWidget(tr("Students"),new MyModel(30,2),this);
    model_dock_widget->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, model_dock_widget);

    //viewMenu->addAction(dock->toggleViewAction());

}

void MainWindow::createRightDockWindows()
{   
    dock_vec[0] = new QDockWidget(tr("Cats"), this);
    dock_vec[0]->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock_vec[0]);
    dock_vec[0]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    dock_vec[0]->setWidget(create_VHLayout());

    
    dock_vec[1] = new QDockWidget(tr("dogs"), this);
    addDockWidget(Qt::RightDockWidgetArea, dock_vec[1]);
    dock_vec[1]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    dock_vec[1]->setWidget(createGridLayout());
    
    tabifyDockWidget(dock_vec[0], dock_vec[1]);
    
    
    connect(menu_dock, &QAction::toggled,this, &MainWindow::ShowDoc);
    connect(toolbar_dock, &QAction::triggered,dock_vec[1], &QDockWidget::raise);
 
    
    
}

QWidget* MainWindow::create_VHLayout()
{
    QWidget* widget = new QWidget();
    QVector<QString> str= {"One","Two","Three","Four","Five"};
    QVector<QPushButton*> buttons(5);
    for (int i = 0;i<buttons.size();i++)
        {
                buttons[i]= new QPushButton(str[i]);
 
        }
    QHBoxLayout *vlayout = new QHBoxLayout();
    for(int i = 0;i<3;i++)
        vlayout->addWidget(buttons[i]);
    QVBoxLayout *hlayout = new QVBoxLayout();
    hlayout->addLayout(vlayout);
    hlayout->addWidget(buttons[3]);
    hlayout->addWidget(buttons[4]);
    hlayout->insertStretch( -1, 1 );
    widget->setLayout(hlayout);
    widget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    return widget;


}

QWidget* MainWindow::createGridLayout()
{
    QWidget* widg = new QWidget();
    QVector<QVector<int>> grid_vec = {{0,0,1,1},
				      {0,1,1,1},
				      {0,2,1,1},
				      {1,0,1,3},
				      {2,0,1,3}};
    QVector<QString> str= {"One","Two","Three","Four","Five"};

    QGridLayout *layout = new QGridLayout();
    QVector<QPushButton*> grid_buttons(5);
    for (int i = 0;i<grid_buttons.size();i++)
         {
                 grid_buttons[i] = new QPushButton(str[i]);
         }
    for (int i=0;i< grid_buttons.size();i++)
        {
                layout->addWidget(grid_buttons[i], grid_vec[i][0], grid_vec[i][1],grid_vec[i][2],grid_vec[i][3]);
        }

    widg->setLayout(layout);
    widg->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
  //  widget->show();

    return widg;



}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,menu_vec(3)
    ,dock_vec(2) {
	setMinimumSize(500,500);

        createMenus();
	createToolBars();
// 	createActions();
        createLeftDockWindow();
	createRightDockWindows();
        centralWidget();
        
}
