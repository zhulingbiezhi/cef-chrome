#ifndef _QCEFFOCUSHANDLER_H_
#define _QCEFFOCUSHANDLER_H_

#include "include/cef_focus_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefFocusHandler : public CefFocusHandler
{
public:
	QCefFocusHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefFocusHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefFocusHandler);

	virtual void OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next);

	virtual bool OnSetFocus(CefRefPtr<CefBrowser> browser, FocusSource source);

	virtual void OnGotFocus(CefRefPtr<CefBrowser> browser);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFFOCUSHANDLER_H_