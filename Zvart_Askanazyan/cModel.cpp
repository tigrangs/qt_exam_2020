#include "cModel.h"
#include <QString>
#include <QTableView>
#include <QBrush>

CustomModel::CustomModel(QObject *parent ) : QAbstractTableModel(parent)
{
    init();
}
int CustomModel::rowCount(const QModelIndex& parent) const {

        Q_UNUSED(parent);   
        return m_Student.size();
}
int CustomModel::columnCount(const QModelIndex& parent) const {

        Q_UNUSED(parent);
        return 2;
}
QVariant CustomModel::data(const QModelIndex &index, int role ) const
{
    if (!index.isValid()) {
         return QVariant();
    }
    if( role == Qt::DisplayRole) {
      const Student& info = m_Student.at(index.row());
      switch (index.column()) {
          case 0:
             return info.getName();
          case 1:
             return info.getNumber();
          default:
             return QVariant();
      }
    }  
    return QVariant();
}

bool CustomModel::setData(const QModelIndex &index, const QVariant &value, int role )
{
   if (index.isValid() && role == Qt::EditRole) {
     Student info = m_Student.at(index.row());
      switch(index.column()) {

        case 1: 
        {
            info.setNumber(value.toInt());
            m_Student.replace(index.row(),info);
        }
            break;
        default:
            return false;
      }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant CustomModel::headerData(int section, Qt::Orientation orientation,int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
            case 0:
                return QString("Student Name"); break;
            case 1:
                return QString("Number"); break;
            default:
                return QVariant(); break;
        }
    } 
    else if(orientation == Qt::Vertical && role == Qt::DisplayRole) {
        return QString(" %1 ").arg(++section);
    }
    return QVariant();
}

Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const {

     if(index.isValid() && !(index.column() == 0)) {
           return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
     }
}

void CustomModel::init()
{
    m_Student.append(Student("Yeghiazaryan Tatevik", 1));
    m_Student.append(Student("Hunanyan Lilit",       2));
    m_Student.append(Student("Ter-Ghazaryan Zaruhi", 3));
    m_Student.append(Student("Baghdasaryan Liana",   4));
    m_Student.append(Student("Ayvazyan Argishty",    5));
    m_Student.append(Student("Khachatryan Tigran",   6));
    m_Student.append(Student("Askanazyan Zvart",     7));
    m_Student.append(Student("Aslikyan Zhora",       8));
    m_Student.append(Student("Bejanyan Vahag",       9));
    m_Student.append(Student("Harutyunyan Liana",   10));
    m_Student.append(Student("Aydinyan Narek",      11));
    m_Student.append(Student("Hambardzumyan Nane",  12));
    m_Student.append(Student("Verdyan Arthur",      13));
    m_Student.append(Student("Khachatryan Lilia",   14));
    m_Student.append(Student("Nikoghosyan Karen",   15));
    m_Student.append(Student("Revazyan Davit",      16));
    m_Student.append(Student("Antonyan Armen",      17));
    m_Student.append(Student("Eghishyan Volodia",   18));
    m_Student.append(Student("Galstyan Viktor",     19));
    m_Student.append(Student("Harutyunyan Eduard",  20));
    m_Student.append(Student("Yurdamyan Nshan",     21));
    m_Student.append(Student("Stepanyan Lilia",     22));
    m_Student.append(Student("Grigoryan Veronika",  23));
    m_Student.append(Student("Mirzakhanyan Sero",   24));
    m_Student.append(Student("Tamazyan Tigran",     25));
    m_Student.append(Student("Galstyan Davit",      26));
    m_Student.append(Student("Gabrielyan Hovsep",   27));
    m_Student.append(Student("Abroyan Vardan",      28));
    m_Student.append(Student("Karapetyan Robert",   29));
    m_Student.append(Student("Davtyan Vachagan",    30));
    m_Student.append(Student("Mirzoyan Arman",      31));

}


















