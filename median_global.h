#ifndef MEDIAN_GLOBAL_H
#define MEDIAN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MEDIAN_LIBRARY)
#  define MEDIAN_EXPORT Q_DECL_EXPORT
#else
#  define MEDIAN_EXPORT Q_DECL_IMPORT
#endif

#endif // MEDIAN_GLOBAL_H
