#ifndef _Q_CEFINVOKER_H_
#define _Q_CEFINVOKER_H_

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
#define QCEFVIEW_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "QCefView.lib")
#endif

#include <QObject>

class QCEFVIEW_EXPORT QCefInvoker : public QObject
{
	//Q_OBJECT
public:
	QCefInvoker();
	virtual ~QCefInvoker();

private:

};

#endif //_QCEFINVOKER_H_