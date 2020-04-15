#include "Info.h"

Student::Student()
               : m_Name(QString())
               , m_Number(int())
{
}
Student::Student(QString name,int number)
               :m_Name(name)
               ,m_Number(number)
{
}
          
QString Student::getName()  const { return m_Name;}

int     Student::getNumber()  const { return m_Number;}
   
void    Student::setNumber(int number)  {m_Number = number;}
          
QDebug operator<<(QDebug dbg, const Student &info) {
    dbg << info.m_Name;
    dbg << info.m_Number;
    return dbg;
}

