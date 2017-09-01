#ifndef _QCEFLOADHANDLER_H_
#define _QCEFLOADHANDLER_H_

#include "include/cef_load_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefLoadHandler : public CefLoadHandler
{
public:
	QCefLoadHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefLoadHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefLoadHandler);

	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward);

	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);

	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode);

	virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFLOADHANDLER_H_