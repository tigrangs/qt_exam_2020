#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QString>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyModel(QObject* parent = nullptr);
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

public slots:
    //needs for filtering
    void filterAccepted(const QString& line);

};

#endif //PROXYMODEL_H

