#ifndef _QCEFKEYBOARDHANDLER_H_
#define _QCEFKEYBOARDHANDLER_H_

#include "include/cef_keyboard_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefKeyboardHandler : public CefKeyboardHandler
{
public:
	QCefKeyboardHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefKeyboardHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefKeyboardHandler);

	virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event, bool* is_keyboard_shortcut);

	virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFKEYBOARDHANDLER_H_