#ifndef DORK_COMMIT_H
#define DORK_COMMIT_H

#include <QDjangoModel.h>
#include "libdork_global.h"
namespace dork {

class LIBDORKSHARED_EXPORT Commit  : public QDjangoModel
{
    Q_OBJECT
public:
    explicit Commit(QObject *parent = 0);


};

} // namespace dork

#endif // DORK_COMMIT_H
