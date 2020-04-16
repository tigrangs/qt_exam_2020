#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    studs.append(QPair<QString, int>("Yeghiazaryan Tatevik", 1));
    studs.append(QPair<QString, int>("Hunanyan Lilit",       2));
    studs.append(QPair<QString, int>("Ter-Ghazaryan Zaruhi", 3));
    studs.append(QPair<QString, int>("Baghdasaryan Liana",   4));
    studs.append(QPair<QString, int>("Ayvazyan Argishty",    5));
    studs.append(QPair<QString, int>("Khachatryan Tigran",   6));
    studs.append(QPair<QString, int>("Askanazyan Zvart",     7));
    studs.append(QPair<QString, int>("Aslikyan Zhora",       8));
    studs.append(QPair<QString, int>("Bejanyan Vahag",       9));
    studs.append(QPair<QString, int>("Harutyunyan Liana",   10));
    studs.append(QPair<QString, int>("Aydinyan Narek",      11));
    studs.append(QPair<QString, int>("Hambardzumyan Nane",  12));
    studs.append(QPair<QString, int>("Verdyan Arthur",      13));
    studs.append(QPair<QString, int>("Khachatryan Lilia",   14));
    studs.append(QPair<QString, int>("Nikoghosyan Karen",   15));
    studs.append(QPair<QString, int>("Revazyan Davit",      16));
    studs.append(QPair<QString, int>("Antonyan Armen",      17));
    studs.append(QPair<QString, int>("Eghishyan Volodia",   18));
    studs.append(QPair<QString, int>("Galstyan Viktor",     19));
    studs.append(QPair<QString, int>("Harutyunyan Eduard",  20));
    studs.append(QPair<QString, int>("Yurdamyan Nshan",     21));
    studs.append(QPair<QString, int>("Stepanyan Lilia",     22));
    studs.append(QPair<QString, int>("Grigoryan Veronika",  23));
    studs.append(QPair<QString, int>("Mirzakhanyan Sero",   24));
    studs.append(QPair<QString, int>("Tamazyan Tigran",     25));
    studs.append(QPair<QString, int>("Galstyan Davit",      26));
    studs.append(QPair<QString, int>("Gabrielyan Hovsep",   27));
    studs.append(QPair<QString, int>("Abroyan Vardan",      28));
    studs.append(QPair<QString, int>("Karapetyan Robert",   29));
    studs.append(QPair<QString, int>("Davtyan Vachagan",    30));
    studs.append(QPair<QString, int>("Mirzoyan Arman",      31));
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return studs.size();
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if(section == 0){
            return QString("Name");
        }
        else if(section == 1){
            return QString("Number");
        }
    }

    if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }

    return QVariant();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    if (role == Qt::DisplayRole)
    {
        if(index.column() == 0){
            return studs[index.row()].first;
        }
        else if(index.column() == 1){
            return studs[index.row()].second;
        }
        else
            return  {};
    }

    return QVariant();
}


bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (!checkIndex(index) || index.column() == 0)
        {
            return false;
        }

        studs[index.row()].second = value.toInt();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

