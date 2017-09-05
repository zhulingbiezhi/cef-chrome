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

// #ifdef DEBUG_INFORMATION
// #define  DEBUG_INFO(args...)  qDebug() << __FUNCTION__ << args;
// #else
// #define  DEBUG_INFO(args...)  qWarning() << __FUNCTION__ << args;
// #endif // DEBUG_INFORMATION

//#define QCEF_QUERY_NAME						"QCefQuery"
//#define QCEF_QUERY_CANCEL_NAME				"QCefQueryCancel"
//#define QCEF_OBJECT_NAME					"QCefClient"
//#define INVOKEMETHOD_NOTIFY_MESSAGE			"NotifyRequestMessage"
//#define TRIGGEREVENT_NOTIFY_MESSAGE			"TriggerEventMessage"

