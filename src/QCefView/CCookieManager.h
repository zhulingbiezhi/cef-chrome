#ifndef _CCookieManager_H_
#define _CCookieManager_H_
#include <QString>
#include <include/cef_cookie.h>
#include "inc/QCefCommon.h"

#include <QDateTime>

class CCefSetCookieCallback;
class QCefCookieVisitor;
class CCefCompletionCallback;

class CCookieManager 
{
public:
	CCookieManager();
	~CCookieManager();

	static CCookieManager& getInstance();

	void setCookie(const QString& url, const QString& key, const QString& value);
	void getUrlCookie(const QString& url, QList<TCefCookie>& cookieList);
	void getAllCookie(QList<TCefCookie>& cookieList);

	CefRefPtr<CefCookieManager>  getManager();

protected:
private:
	QDateTime  CefTimeToQt(const cef_time_t& cef_time);
	cef_time_t QtTimeToCef(const QDateTime&  dateTime);

private:
	CefRefPtr<CCefSetCookieCallback>  mpSetCookieCall;
	CefRefPtr<CCefCompletionCallback>  mpGetManagerCallback;
	CefRefPtr<CefCookieManager>		  mpCookieManager;
	CefRefPtr<QCefCookieVisitor>	  mpCookieVistor;
};

class CCefCompletionCallback : public CefCompletionCallback
{
public:
	CCefCompletionCallback();
	~CCefCompletionCallback();

	virtual void OnComplete();

protected:

private:
	IMPLEMENT_REFCOUNTING(CCefCompletionCallback);
};

class CCefSetCookieCallback : public CefSetCookieCallback
{
public:
	CCefSetCookieCallback();
	~CCefSetCookieCallback();

	virtual void OnComplete(bool success);

protected:

private:
	IMPLEMENT_REFCOUNTING(CCefSetCookieCallback);
};


#endif //_CCookieManager_H_