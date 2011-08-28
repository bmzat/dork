#ifndef DORK_DIRTREE_H
#define DORK_DIRTREE_H

#include <QDjangoModel.h>
#include "libdork_global.h"
namespace dork {

class LIBDORKSHARED_EXPORT DirTree : public QDjangoModel
{
    Q_OBJECT
public:
    explicit DirTree(QObject *parent = 0);

};

} // namespace dork

#endif // DORK_DIRTREE_H
