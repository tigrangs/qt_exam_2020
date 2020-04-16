#include<QDialog>
#include<QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QDialogButtonBox>
#include<QApplication>
#include<QAction>
class MyDialog : public QDialog
    {
        Q_OBJECT
 
        public:
        explicit MyDialog(QAction* act,QWidget * parent = 0);
        ~MyDialog(){ }
 
        private:
 	QAction* act;
        QPushButton*     m_pOkButton;              
        QPushButton*     m_pCancelButton;    
        QDialogButtonBox*  m_pDialogButtonBox;
 
        QVBoxLayout*         m_pDialogLayout;
 
 
        public slots:
 
        void OnOk_Slot(void);
        void OnCancel_Slot(void);
     };
