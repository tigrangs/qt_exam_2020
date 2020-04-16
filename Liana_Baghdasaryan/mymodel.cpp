#include"mymodel.h"
#include<QBrush>
#include<QColor>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<QStandardItem>
#include<QRegExp>
MyModel::MyModel(int row, int column,QObject *parent)
    : QAbstractTableModel(parent)
    ,Row_count(row)
    ,column_count(column)
    ,m_vecGriddata{row,QVector<QString>{column,0}}
{
 
    QFile file("names.txt");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
	int i = 0;
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            m_vecGriddata[i][0] = line;
	    i++;
	  
        }
        file.close();
    }
}

int MyModel::rowCount(const QModelIndex & ) const
{
   return Row_count;
}

Qt::ItemFlags MyModel::flags(const QModelIndex& index) const
{
	if (index.column()==0)
		return QAbstractTableModel::flags(index) ;
	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable; 	 // | Qt::ItemIsUserCheckable;
}
bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{


    if (role == Qt::EditRole) {
        if (!index.isValid())
            return false;
        
	QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
	if (re.exactMatch(value.toString()))
		{
			m_vecGriddata[index.row()][index.column()] = value.toString();
        		return true;
		}
	
		return false;
	}

}
int MyModel::columnCount(const QModelIndex &) const
{
    return column_count;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
	{
		return QVariant();
	}
	
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
	{

	       return QString("%1")
        	           .arg(m_vecGriddata[index.row()][index.column()]);

   	       return QVariant();	
	}
	if (role == Qt::BackgroundRole)
	{
		return QBrush(Qt::red);
	}
	return QVariant();
}



QVariant MyModel::headerdata(int section,Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
       {
        switch(section) 
	{
            case 0:
                return QString("Student Name"); break;
      
	    case 1:
                return QString("Number"); break;
	    default:
                return QVariant(); break;
        }

    }
}
