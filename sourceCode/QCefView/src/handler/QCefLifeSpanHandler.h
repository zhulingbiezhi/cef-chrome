#ifndef _QCEFLIFESPANHANDLER_H_
#define _QCEFLIFESPANHANDLER_H_

#include "include/cef_life_span_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefLifeSpanHandler : public CefLifeSpanHandler
{
public:
	QCefLifeSpanHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefLifeSpanHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefLifeSpanHandler);

	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access);

	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);

	virtual bool DoClose(CefRefPtr<CefBrowser> browser);

	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

	QCefViewBrowserHandler * m_pBrowserHandler;

};



#endif //_QCEFLIFESPANHANDLER_H_