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
	qDebug() << __FUNCTION__ << next;
}

bool QCefFocusHandler::OnSetFocus(CefRefPtr<CefBrowser> browser, FocusSource source)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
	return false;
}

void QCefFocusHandler::OnGotFocus(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
}
