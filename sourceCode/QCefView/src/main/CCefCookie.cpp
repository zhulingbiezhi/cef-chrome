#include "CCefCookie.h"


#include <QEventLoop>

#include <include/cef_task.h>
#include <include/cef_runnable.h>
#include "QCefCookieVisitor.h"

#if defined(CEF_STRING_TYPE_UTF16)
	#define StrToQString QString::fromWCharArray
#elif defined(CEF_STRING_TYPE_UTF8)
	#define StrToQString QString::fromUtf8
#elif defined(CEF_STRING_TYPE_WIDE)
	#define StrToQString QString::fromWCharArray
#endif

CCefCookie::CCefCookie()
{
	qDebug() << __FUNCTION__;
	mpGetManagerCallback = new CCefCompletionCallback();
	mpCookieManager = CefCookieManager::GetGlobalManager(mpGetManagerCallback.get());
	mpSetCookieCall = new CCefSetCookieCallback();
	mpCookieVistor = new QCefCookieVisitor();
}

CCefCookie::~CCefCookie()
{

}

CCefCookie& CCefCookie::getInstance()
{
	static CCefCookie s_Instance;
	return s_Instance;
}

void CCefCookie::setCookie(const QString& url, const QString& key, const QString& value)
{
	CefString cef_url;
	cef_url.FromString(url.toLatin1().data());

	CefCookie cookie;
	CefString(&cookie.name).FromString(key.toLatin1().data());
	CefString(&cookie.value).FromString(value.toLatin1().data());
	CefString(&cookie.domain).FromString(url.toLatin1().data());
	CefString(&cookie.path).FromASCII("/");
	cookie.has_expires = false;
	cookie.creation = QtTimeToCef(QDateTime::currentDateTime());

	CefPostTask(TID_IO, NewCefRunnableMethod(mpCookieManager.get(), &CefCookieManager::SetCookie, cef_url, cookie, mpSetCookieCall));
}

void CCefCookie::getUrlCookie(const QString& url, QList<TCefCookie>& cookieList)
{
	CefString cefUrl;
	cefUrl.FromString(url.toLatin1().data());
	mpCookieManager->VisitUrlCookies(cefUrl, false, mpCookieVistor);
	QEventLoop loop;
	QObject::connect(mpCookieVistor, &QCefCookieVisitor::sigVisitFinished, &loop, &QEventLoop::quit);
	loop.exec();
	QList<CefCookie> cefCookieList = mpCookieVistor->getCookies();
	for each(CefCookie cookie in cefCookieList)
	{
		TCefCookie qtCookie;
		qtCookie.cookieName = StrToQString(cookie.name.str);
		qtCookie.cookieValue = StrToQString(cookie.value.str);
		qtCookie.host = StrToQString(cookie.domain.str);
		qtCookie.path = StrToQString(cookie.path.str);
		qtCookie.secure = cookie.secure;
		qtCookie.has_expires = cookie.has_expires;
		qtCookie.httponly = cookie.httponly;
		qtCookie.creation = CefTimeToQt(cookie.creation);
		qtCookie.last_access = CefTimeToQt(cookie.last_access);
		if (qtCookie.has_expires)
		{
			qtCookie.expires = CefTimeToQt(cookie.expires);
			qDebug() << __FUNCTION__ << qtCookie.expires.toString("yyyy-MM-dd hh:mm:ss");
		}
		qDebug() << qtCookie.creation.toString("yyyy-MM-dd hh:mm:ss") << qtCookie.last_access.toString("yyyy-MM-dd hh:mm:ss");
		cookieList.append(qtCookie);
	}	
}

void CCefCookie::getAllCookie(QList<TCefCookie>& cookieList)
{
	mpCookieManager->VisitAllCookies(mpCookieVistor);
	QEventLoop loop;
	QObject::connect(mpCookieVistor, &QCefCookieVisitor::sigVisitFinished, &loop, &QEventLoop::quit);
	loop.exec();
	
	QList<CefCookie> cefCookieList = mpCookieVistor->getCookies();
	qDebug() << __FUNCTION__ << "finish read" << cefCookieList.size();
	for each(CefCookie cookie in cefCookieList)
	{
		TCefCookie qtCookie;
		qtCookie.cookieName = StrToQString(cookie.name.str);
		qtCookie.cookieValue = StrToQString(cookie.value.str);
		qtCookie.host = StrToQString(cookie.domain.str);
		qtCookie.path = StrToQString(cookie.path.str);
		qtCookie.secure = cookie.secure;
		qtCookie.has_expires = cookie.has_expires;
		qtCookie.httponly = cookie.httponly;
		qtCookie.creation = CefTimeToQt(cookie.creation);
		qtCookie.last_access = CefTimeToQt(cookie.last_access);
		if (qtCookie.has_expires)
		{
			qtCookie.expires = CefTimeToQt(cookie.expires);
			qDebug() << __FUNCTION__ << qtCookie.expires.toString("yyyy-MM-dd hh:mm:ss");
		}
		qDebug() << qtCookie.creation.toString("yyyy-MM-dd hh:mm:ss") << qtCookie.last_access.toString("yyyy-MM-dd hh:mm:ss");
		cookieList.append(qtCookie);
	}
}

CefRefPtr<CefCookieManager> CCefCookie::getManager()
{
	return mpCookieManager;
}

QDateTime CCefCookie::CefTimeToQt(const cef_time_t& cef_time)
{
	QStringList strTimeList;
	strTimeList.append(QString("%1").arg(cef_time.year, 4, 10, QChar('0'))); 
	strTimeList.append(QString("%1").arg(cef_time.month, 2, 10, QChar('0'))); 
	strTimeList.append(QString("%1").arg(cef_time.day_of_month, 2, 10, QChar('0')));
	strTimeList.append(QString("%1").arg(cef_time.hour, 2, 10, QChar('0'))); 
	strTimeList.append(QString("%1").arg(cef_time.minute, 2, 10, QChar('0')));
	strTimeList.append(QString("%1").arg(cef_time.second, 2, 10, QChar('0')));
	QString strTime = strTimeList.join("-");
	return	QDateTime::fromString(strTime, "yyyy-MM-dd-hh-mm-ss");
}

cef_time_t CCefCookie::QtTimeToCef(const QDateTime& dateTime)
{
	cef_time_t cef_time;
	cef_time.year =  dateTime.date().year();
	cef_time.month = dateTime.date().month();
	cef_time.day_of_week = dateTime.date().dayOfWeek();
	cef_time.hour = dateTime.time().hour();
	cef_time.minute = dateTime.time().minute();
	cef_time.second = dateTime.time().second();
	return cef_time;
}

CCefSetCookieCallback::CCefSetCookieCallback()
{

}

CCefSetCookieCallback::~CCefSetCookieCallback()
{

}

void CCefSetCookieCallback::OnComplete(bool success)
{
	qDebug() << __FUNCTION__ << success;
}

CCefCompletionCallback::CCefCompletionCallback()
{

}

CCefCompletionCallback::~CCefCompletionCallback()
{

}

void CCefCompletionCallback::OnComplete()
{
	qDebug() << __FUNCTION__;
}
