#ifndef DORK_BLOB_H
#define DORK_BLOB_H

#include <QObject>

namespace dork {

class Blob : public QObject
{
    Q_OBJECT
public:
    explicit Blob(QObject *parent = 0);

signals:

public slots:

};

} // namespace dork

#endif // DORK_BLOB_H
