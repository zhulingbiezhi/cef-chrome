#include "QCefDragHandler.h"
#include "QCefViewBrowserHandler.h"

QCefDragHandler::QCefDragHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefDragHandler::~QCefDragHandler()
{

}

bool QCefDragHandler::OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, DragOperationsMask mask)
{
	CEF_REQUIRE_UI_THREAD();
	std::vector<CefString> names;
	dragData->GetFileNames(names);
	QString url = QString::fromStdString(names[0].ToString());
	qDebug() << __FUNCTION__ << url;
	m_pBrowserHandler->hostWidget_->navigateToUrl(url);
	return false;
}
