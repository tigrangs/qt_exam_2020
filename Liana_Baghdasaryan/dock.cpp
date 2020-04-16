#include"dock.h"
#include<QTableView>   
#include<QGridLayout>
#include<QWidget>
#include<QMainWindow>
MyModelDockWidget::MyModelDockWidget(const QString &title, MyModel* model,QWidget* parent)
	:QDockWidget(title,parent)
	,model(model)
{
   QTableView *tableView=new QTableView;
   tableView->setModel(model);
   setWidget(tableView);
}


  MyModel* MyModelDockWidget::get_model()
	{
		return model;
	}

   MyGridDockWidget::MyGridDockWidget(const QString &title,QWidget* parents)
				:QDockWidget(title,parents)
				
	{

	}
   void MyGridDockWidget::set_grid(QVector<QVector<int>> grid,QVector<QString> but_names)
   {

	QWidget* widg2 = new QWidget();
       QGridLayout *layout = new QGridLayout();
       for (int i = 0;i<grid.size();i++)
       {
               buttons[i] = new QPushButton(but_names[i]);
      }
      for (int i=0;i< buttons.size();i++)
      {
              layout->addWidget(buttons[i], grid[i][0], grid[i][1],grid[i][2],grid[i][3]);
      }
    widg2->setLayout(layout);
    setWidget(widg2);


   }






