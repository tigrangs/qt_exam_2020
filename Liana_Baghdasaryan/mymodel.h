#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    MyModel(int row, int column,QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerdata(int section,Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
	int Row_count;
	int column_count;
	QVector<QVector<QString>> m_vecGriddata;
};
