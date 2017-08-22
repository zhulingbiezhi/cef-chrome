#include "QCefCookieVisitor.h"
#include <QDebug>
QCefCookieVisitor::QCefCookieVisitor()
{

}

QCefCookieVisitor::~QCefCookieVisitor()
{

}

bool QCefCookieVisitor::Visit(const CefCookie& cookie, int count, int total, bool& deleteCookie)
{
	if (count == 0)
	{
		mCookieHash.clear();
	}
	mCookieHash.insert(QString::fromStdWString(cookie.domain.str), cookie);
	qDebug() << __FUNCTION__ << QString::fromStdString(CefString(&cookie.name).ToString()) << QString::fromStdString(CefString(&cookie.value).ToString()) << QString::fromStdString(CefString(&cookie.domain).ToString()) << QString::fromStdString(CefString(&cookie.path).ToString());
	qDebug() << __FUNCTION__ << count << total << deleteCookie;
	if (count == total - 1)
	{
		emit sigVisitFinished();
	}
	return true;
}

QList<CefCookie> QCefCookieVisitor::getCookies()
{
	QHashIterator<QString, CefCookie> it(mCookieHash);
	QList<CefCookie>  cookieList;
	while (it.hasNext())
	{
		it.next();
		cookieList.append(mCookieHash.values(it.key()));
	}
	return cookieList;
}
