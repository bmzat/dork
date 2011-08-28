#ifndef DORK_BRANCH_H
#define DORK_BRANCH_H

#include <QObject>
#include <QDjangoModel.h>
#include "libdork_global.h"
namespace dork {

class LIBDORKSHARED_EXPORT Branch : public QDjangoModel
{
    Q_OBJECT
public:
    explicit Branch(QObject *parent = 0);

signals:

public slots:

};

} // namespace dork

#endif // DORK_BRANCH_H
