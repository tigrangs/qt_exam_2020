#pragma once
#include"dock.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include<QToolBar>
#include<dialog.h>
#include<QMenu>
#include"proxy.h"
class MainWindow : public QMainWindow {
    
  Q_OBJECT  
private slots:
	void ShowDoc(bool);
  private:
   QWidget* main_widget;
   MyModelDockWidget* model_dock_widget;
   QVector<QDockWidget*> dock_vec;
   QVector<QMenu*> menu_vec;
   QToolBar* toolbar; 
   QDialog* dialog;
   MyProxy* proxy;
//Menu Actions
private:

  QAction *menu_quit;
  QAction* menu_check_quit;
  QAction* menu_dock;

//ToolBar actions
  QAction* toolbar_quit;
  QAction* toolbar_exit;
  QAction* toolbar_dock;
  private:
    QWidget* create_VHLayout();
    QWidget* createGridLayout();
    void createMenus();
    void createToolBars();
    void centralWidget();
    void createRightDockWindows();
    void createLeftDockWindow();
public:
    MainWindow(QWidget *parent = 0);
};
