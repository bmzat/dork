#include "blob.h"

namespace dork {

Blob::Blob(QObject *parent):QDjangoModel(parent)
{
}

}

QString dork::Blob::key()
{
    return mKey;
}

QDateTime dork::Blob::creationTimestamp()
{
    return mCreationTimestamp;
}

qint64 dork::Blob::size()
{
    return mSize;
} // namespace dork
