#ifndef DORK_BRANCH_H
#define DORK_BRANCH_H

#include <QDjangoModel.h>

namespace dork {

class Branch : public QDjangoModel
{
    Q_OBJECT
public:
    explicit Branch(QObject *parent = 0);

signals:

public slots:

};

} // namespace dork

#endif // DORK_BRANCH_H
