#include<QDockWidget>
#include"mymodel.h"
#include<QPushButton>

class MyModelDockWidget:public QDockWidget

{
public:
   MyModelDockWidget(const QString &title,MyModel* model, QWidget *parent = nullptr);
   MyModel* get_model();

private:
MyModel* model;  


};

class MyGridDockWidget:public QDockWidget

{
public:
   MyGridDockWidget(const QString &title,QWidget *parent = nullptr);
   void set_grid(QVector<QVector<int>> grid,QVector<QString> but_names);

private:
QVector<QPushButton*> buttons;


};
