#ifndef _QCEFDISPLAYHANDLER_H_
#define _QCEFDISPLAYHANDLER_H_

#include "include/cef_display_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefDisplayHandler : public CefDisplayHandler
{
public:
	QCefDisplayHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefDisplayHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefDisplayHandler);

	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url);

	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);

	virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen);

	virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value);

	virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line);

	QCefViewBrowserHandler * m_pBrowserHandler;
};



#endif //_QCEFDISPLAYHANDLER_H_