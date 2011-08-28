#ifndef DORK_BLOB_H
#define DORK_BLOB_H

#include <QObject>
#include <QDjangoModel.h>

namespace dork {

class Blob : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key)
    Q_PROPERTY(QDateTime creationTimestamp READ creationTimestamp)
    Q_PROPERTY(qint64 size READ size)
    Q_CLASSINFO("key","primary_key=true")
public:
    explicit Blob(QObject *parent = 0);
    QString key();
    QDateTime creationTimestamp();
    qint64 size();
signals:

public slots:

private:
    QString mKey;
    qint64 mSize;
    QDateTime mCreationTimestamp;
};

} // namespace dork

#endif // DORK_BLOB_H
