#include "QCefDialogHandler.h"
#include "QCefViewBrowserHandler.h"

QCefDialogHandler::QCefDialogHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefDialogHandler::~QCefDialogHandler()
{
	
}

bool QCefDialogHandler::OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode, const CefString& title, const CefString& default_file_path, const std::vector<CefString>& accept_filters, int selected_accept_filter, CefRefPtr<CefFileDialogCallback> callback)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	return false;
}
