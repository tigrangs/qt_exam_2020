#include "myproxymodel.h"

MyProxyModel::MyProxyModel(QObject* parent) : QSortFilterProxyModel(parent)
{

}

void MyProxyModel::filterStringReceived(const QString &filter)
{
    setFilterFixedString(filter);
}
