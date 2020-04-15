#include "proxyModel.h"
#include <QVariant>

ProxyModel::ProxyModel(QObject* parent):QSortFilterProxyModel(parent)
{
}

bool ProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if(!source_right.isValid() && !source_left.isValid()) {
        return false;
    }
     QVariant leftData = sourceModel()->data(source_left);
     QVariant rightData = sourceModel()->data(source_right);
     return leftData.toString() < rightData.toString();
}

void ProxyModel::filterAccepted(const QString& line){

    setFilterFixedString(line);
}
