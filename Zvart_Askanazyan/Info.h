#ifndef INFO_H
#define INFO_H

#include <QString>
#include <QDebug>

class Student {
    public: 
        Student();
        Student(QString name,int number);
                
        QString getName()  const;
        int     getNumber()  const;
        void    setNumber(int data);
        
        friend QDebug operator<<(QDebug dbg, const Student &info);
    private:
        QString m_Name;
        int     m_Number;
};
#endif //INFO_H
