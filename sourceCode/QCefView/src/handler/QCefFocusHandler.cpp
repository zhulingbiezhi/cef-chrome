#include "QCefFocusHandler.h"
#include "QCefViewBrowserHandler.h"

QCefFocusHandler::QCefFocusHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefFocusHandler::~QCefFocusHandler()
{

}

void QCefFocusHandler::OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
}

bool QCefFocusHandler::OnSetFocus(CefRefPtr<CefBrowser> browser, FocusSource source)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	return false;
}

void QCefFocusHandler::OnGotFocus(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
}
