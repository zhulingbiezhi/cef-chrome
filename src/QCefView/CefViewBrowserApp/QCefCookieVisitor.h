#pragma once
#include "include\cef_cookie.h"

#include <QHash>
#include <QObject>

class QCefCookieVisitor : public QObject, public CefCookieVisitor
{
	Q_OBJECT
public:
	QCefCookieVisitor();
	virtual ~QCefCookieVisitor();

	virtual bool Visit(const CefCookie& cookie, int count, int total, bool& deleteCookie);

	QList<CefCookie> getCookies();

signals:
	void  sigVisitFinished();


private:
	QHash<QString, CefCookie>		mCookieHash;

	IMPLEMENT_REFCOUNTING(QCefCookieVisitor);
};

