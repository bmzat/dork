#ifndef LIBDORK_GLOBAL_H
#define LIBDORK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDORK_LIBRARY)
#  define LIBDORKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDORKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBDORK_GLOBAL_H
