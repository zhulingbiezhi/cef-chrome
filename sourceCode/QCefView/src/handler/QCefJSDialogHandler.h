#ifndef _QCEFJSDIALOGHANDLER_H_
#define _QCEFJSDIALOGHANDLER_H_

#include "include\cef_jsdialog_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefJSDialogHandler : public CefJSDialogHandler
{
public:
	QCefJSDialogHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefJSDialogHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefJSDialogHandler);

	virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, const CefString& accept_lang, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message);

	virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback);

	virtual void OnResetDialogState(CefRefPtr<CefBrowser> browser);

	virtual void OnDialogClosed(CefRefPtr<CefBrowser> browser);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFJSDIALOGHANDLER_H_