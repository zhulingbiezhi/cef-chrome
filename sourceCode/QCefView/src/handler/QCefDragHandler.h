#ifndef _QCEFDRAGHANDLER_H_
#define _QCEFDRAGHANDLER_H_

#include "include/cef_drag_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefDragHandler : public CefDragHandler
{
public:
	QCefDragHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefDragHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefDragHandler);

	virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, DragOperationsMask mask);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFDRAGHANDLER_H_