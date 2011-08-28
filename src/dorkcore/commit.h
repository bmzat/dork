#ifndef DORK_COMMIT_H
#define DORK_COMMIT_H

#include <QDjangoModel.h>

namespace dork {

class Commit : public QDjangoModel
{
    Q_OBJECT
public:
    explicit Commit(QObject *parent = 0);

signals:

public slots:

};

} // namespace dork

#endif // DORK_COMMIT_H
