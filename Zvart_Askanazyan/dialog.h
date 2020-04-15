#ifndef DIALOG_H
#define DIALOG_H
#include <QMessageBox>
#include <QWidget>

class Dialog :public QObject
{
    Q_OBJECT
public:
    Dialog(QObject *parent = nullptr);

public slots:
    void createDialog();

private:
     QMessageBox *msgBox;
};

#endif // DIALOG_H
