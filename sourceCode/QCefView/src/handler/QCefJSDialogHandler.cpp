#include "QCefJSDialogHandler.h"
#include "QCefViewBrowserHandler.h"

QCefJSDialogHandler::QCefJSDialogHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefJSDialogHandler::~QCefJSDialogHandler()
{

}

bool QCefJSDialogHandler::OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, const CefString& accept_lang, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
	return false;
}

bool QCefJSDialogHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
	return false;
}

void QCefJSDialogHandler::OnResetDialogState(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
}

void QCefJSDialogHandler::OnDialogClosed(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
}
