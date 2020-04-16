#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QString>

class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MyProxy(QObject* parent = nullptr);
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

public slots:
    void filterAccepted(const QString& line);

};

