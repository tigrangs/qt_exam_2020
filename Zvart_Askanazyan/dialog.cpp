#include "dialog.h"
#include <QApplication>

Dialog::Dialog(QObject *parent): QObject(parent)
{
    msgBox = new QMessageBox;
}

void Dialog::createDialog() {

    msgBox->setIcon(QMessageBox::Question);
    msgBox->setWindowTitle("Dialog");
    msgBox->setText("Do you want to close this application?");

    msgBox->addButton(QMessageBox::Yes);
    msgBox->addButton(QMessageBox::Cancel);

    if(msgBox->exec() == QMessageBox::Yes){
      QCoreApplication::quit();
    }
}
