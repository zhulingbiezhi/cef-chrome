#ifndef _QCEFDOWNLOADHANDLER_H_
#define _QCEFDOWNLOADHANDLER_H_

#include "include/cef_download_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefDownloadHandler : public CefDownloadHandler
{
public:
	QCefDownloadHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefDownloadHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefDownloadHandler);

	virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFDOWNLOADHANDLER_H_