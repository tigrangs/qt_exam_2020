#include<QLabel>
#include"dialog.h"
#include<QScreen>
#include<QDesktopWidget>
MyDialog::MyDialog(QAction* act,QWidget * parent)
        :act(act)
	,QDialog(parent)
    {
        m_pOkButton = new QPushButton("OK",this);
        connect(m_pOkButton, SIGNAL(clicked()), this,SLOT(OnOk_Slot()));
        m_pCancelButton = new QPushButton ("Cancel", this);
        QObject::connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(OnCancel_Slot()));
 
        m_pDialogButtonBox = new QDialogButtonBox(this);
        m_pDialogButtonBox->addButton(m_pOkButton, QDialogButtonBox::AcceptRole);
        m_pDialogButtonBox->addButton(m_pCancelButton, QDialogButtonBox::RejectRole);
        QLabel *lab = new QLabel(this);
	lab->setText("Do yo want to quit application?");
        m_pDialogLayout = new QVBoxLayout(this);
       m_pDialogLayout->addWidget(lab);

	m_pDialogLayout->addWidget(m_pDialogButtonBox);
	
       const QRect availableGeometry = parent->screen()->availableGeometry();

        move((availableGeometry.width() - width()) / 2,
                    (availableGeometry.height() - height()) / 2);

	setLayout(m_pDialogLayout);
    }
 
    void MyDialog::OnOk_Slot(void)
    {
	QApplication::quit();
        accept();
    }
 
    void MyDialog::OnCancel_Slot()
    {
	act->setChecked(false);
        reject();
    }
