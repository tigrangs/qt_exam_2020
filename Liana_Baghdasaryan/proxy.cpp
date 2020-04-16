#include "proxy.h"
#include <QVariant>


MyProxy::MyProxy(QObject* parent):QSortFilterProxyModel(parent)
{
}

bool MyProxy::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if(!source_right.isValid() && !source_left.isValid()) {
        return false;
    }
     QVariant leftData = sourceModel()->data(source_left);
     QVariant rightData = sourceModel()->data(source_right);
     return leftData.toString() < rightData.toString();
}

void MyProxy::filterAccepted(const QString& line){

    setFilterFixedString(line);
}

