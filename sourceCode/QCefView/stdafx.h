#include <windows.h>
#include <tchar.h>

#include "../public/Common.h"
#include <QDebug>



#if defined(_DEBUG) || defined(DEBUG)
#define QLOG(x)	qDebug() << x
#else
#define QLOG(x)	__noop(x)
#endif

#ifdef DEBUG_FUNCTION
#define  DEBUG_FUNC()  qDebug() << __FUNCTION__
#else
#define  DEBUG_FUNC()  
#endif // DEBUG_FUNCTION
