#include "QCefRequestHandler.h"
#include "QCefViewBrowserHandler.h"

QCefRequestHandler::QCefRequestHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefRequestHandler::~QCefRequestHandler()
{

}

bool QCefRequestHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_redirect)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	m_pBrowserHandler->message_router_->OnBeforeBrowse(browser, frame);
	return false;
} 

bool QCefRequestHandler::OnOpenURLFromTab(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, WindowOpenDisposition target_disposition, bool user_gesture)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	return true;	// return true to cancel this navigation.
}

CefRefPtr<CefResourceHandler> QCefRequestHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request)
{
	CEF_REQUIRE_IO_THREAD();
	DEBUG_FUNC();
	return NULL;
}

void QCefRequestHandler::OnResourceLoadComplete(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response, URLRequestStatus status, int64 received_content_length)
{
	qDebug() << __FUNCTION__ << QString::fromStdString(request->GetURL().ToString()) << received_content_length;
}

bool QCefRequestHandler::OnQuotaRequest(CefRefPtr<CefBrowser> browser, const CefString& origin_url, int64 new_size, CefRefPtr<CefRequestCallback> callback)
{
	CEF_REQUIRE_IO_THREAD();
	DEBUG_FUNC();
	return true;
}

void QCefRequestHandler::OnProtocolExecution(CefRefPtr<CefBrowser> browser, const CefString& url, bool& allow_os_execution)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
}

void QCefRequestHandler::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	browser->GetMainFrame()->LoadURL(browser->GetMainFrame()->GetURL());

	m_pBrowserHandler->message_router_->OnRenderProcessTerminated(browser);
}
