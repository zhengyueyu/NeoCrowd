#ifndef NEOCROWDLIB_GLOBAL_H
#define NEOCROWDLIB_GLOBAL_H


#include <memory>
#include <string>
#include <QtCore/qglobal.h>

#if defined(NEOCROWDLIB_LIBRARY)
#  define NEOCROWDLIB_EXPORT Q_DECL_EXPORT
#else
#  define NEOCROWDLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // NEOCROWDLIB_GLOBAL_H
