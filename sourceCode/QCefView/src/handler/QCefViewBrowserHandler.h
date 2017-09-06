#ifndef QCEFVIEWHANDLER_H_
#define QCEFVIEWHANDLER_H_
#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include <mutex>
#include <QPointer>

#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "include/cef_request_handler.h"
#include "inc/QCefView.h"
#include "QCefQueryHandler.h"

#define CLASS_NAME(class_name) #class_name

class ICefViewBrowser;
class QCefQueryHandler;
class QCefCookieVisitor;
class QCefDownloadHandler;
class QCefContextMenuHandler;
class QCefDisplayHandler;
class QCefDragHandler;
class QCefFocusHandler;
class QCefKeyboardHandler;
class QCefLifeSpanHandler;
class QCefLoadHandler;
class QCefRequestHandler;
class QCefDialogHandler;
class QCefJSDialogHandler;


class QCefViewBrowserHandler : public CefClient
{
	typedef CefRefPtr<CefMessageRouterBrowserSide>	MessageRouterPtr;
	typedef std::set<CefMessageRouterBrowserSide::Handler*> MessageHandlerSet;
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
public:

	QCefViewBrowserHandler(QCefView* host);
	~QCefViewBrowserHandler();

	//////////////////////////////////////////////////////////////////////////
	// CefClient methods:
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();

	virtual CefRefPtr<CefDialogHandler> GetDialogHandler();

	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler();

	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler();

	virtual CefRefPtr<CefDragHandler> GetDragHandler();

	virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler();

	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler();

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();

	virtual CefRefPtr<CefLoadHandler> GetLoadHandler();

	virtual CefRefPtr<CefRequestHandler> GetRequestHandler();

// 	virtual CefRefPtr<CefCookieVisitor> GetCookieHandler()
// 	{
// 		return new QCefCookieVisitor();
//  	}

	virtual CefMessageRouterBrowserSide::Handler* GetCefQueryHandler();

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message);

	void setHostWidget(QCefView* host);

	CefRefPtr<CefBrowser> GetBrowser() const;

	int GetBrowserId() const;

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	void CloseAllPopupBrowsers(bool force_close);

	bool IsClosing() const;

	bool TriggerEvent(const CefRefPtr<CefProcessMessage> msg);

	bool ResponseQuery(int64_t query, bool success, const CefString& response, int error);

	bool DispatchNotifyRequest(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message);

private:
	int browser_count_;
	int main_browser_id_;
	bool is_closing_;
	mutable std::mutex	mtx_;

	CefRefPtr<CefBrowser> main_browser_;

	QPointer<QCefView> hostWidget_;

	MessageRouterPtr message_router_;

	//MessageHandlerSet message_handler_set_;
	QCefQueryHandler* cefquery_handler_;

	std::map<std::string, ICefViewBrowser*> mCefViewHandleMap;

	// List of existing browser windows. Only accessed on the CEF UI thread.
	BrowserList popup_browser_list_;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefViewBrowserHandler);

	friend class QCefCookieVisitor;
	friend class QCefDownloadHandler;
	friend class QCefContextMenuHandler;
	friend class QCefDisplayHandler;
	friend class QCefDragHandler;
	friend class QCefFocusHandler;
	friend class QCefKeyboardHandler;
	friend class QCefLifeSpanHandler;
	friend class QCefLoadHandler;
	friend class QCefRequestHandler;
	friend class QCefDialogHandler;
	friend class QCefJSDialogHandler;
};

#endif