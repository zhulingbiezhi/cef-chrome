#ifndef _QCEFREQUESTHANDLER_H_
#define _QCEFREQUESTHANDLER_H_

#include "include/cef_request_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;


class QCefRequestHandler : public CefRequestHandler
{
public:
	QCefRequestHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefRequestHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefRequestHandler);

	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_redirect);

	virtual bool OnOpenURLFromTab(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, WindowOpenDisposition target_disposition, bool user_gesture);

	virtual CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request);

	virtual void OnResourceLoadComplete(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response, URLRequestStatus status, int64 received_content_length);

	virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser, const CefString& origin_url, int64 new_size, CefRefPtr<CefRequestCallback> callback);

	virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser, const CefString& url, bool& allow_os_execution);

	virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFREQUESTHANDLER_H_