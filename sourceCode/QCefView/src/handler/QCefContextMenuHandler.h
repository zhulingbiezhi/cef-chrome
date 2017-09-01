#ifndef _QCEFCONTEXTMENUHANDLER_H_
#define _QCEFCONTEXTMENUHANDLER_H_

#include "include/cef_context_menu_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefContextMenuHandler : public CefContextMenuHandler
{
public:
	QCefContextMenuHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefContextMenuHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefContextMenuHandler);

	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model);

	virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFCONTEXTMENUHANDLER_H_