#pragma once

#include <QSortFilterProxyModel>
#include <QString>

class MyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MyProxyModel(QObject* parent = nullptr);

public slots:
    void filterStringReceived(const QString& filter);
};
