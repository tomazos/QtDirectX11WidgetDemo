// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef CPPHELPERS_H
#define CPPHELPERS_H

#include <QtCore/QSharedPointer>

#define DeclShared(T) class T; typedef QSharedPointer<T> P##T;
#define FwdDeclShared(T) DeclShared(T)

#endif // CPPHELPERS_H
