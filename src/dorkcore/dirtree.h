#ifndef DORK_DIRTREE_H
#define DORK_DIRTREE_H

#include <QDjangoModel.h>

namespace dork {

class DirTree : public QDjangoModel
{
    Q_OBJECT
public:
    explicit DirTree(QObject *parent = 0);

signals:

public slots:

};

} // namespace dork

#endif // DORK_DIRTREE_H
