#include "QCefDownloadHandler.h"
#include "QCefViewBrowserHandler.h"

QCefDownloadHandler::QCefDownloadHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefDownloadHandler::~QCefDownloadHandler()
{

}

void QCefDownloadHandler::OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback)
{
	qDebug() << __FUNCTION__;
}
