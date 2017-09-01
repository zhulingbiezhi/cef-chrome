#ifndef _QCEFDIALOGHANDLER_H_
#define _QCEFDIALOGHANDLER_H_

#include "include\cef_dialog_handler.h"
#include <include/wrapper/cef_helpers.h>

class QCefViewBrowserHandler;

class QCefDialogHandler : public CefDialogHandler
{
public:
	QCefDialogHandler(QCefViewBrowserHandler * pBrowserHandler);
	~QCefDialogHandler();
protected:

private:
	IMPLEMENT_REFCOUNTING(QCefDialogHandler);

	virtual bool OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode, const CefString& title, const CefString& default_file_path, const std::vector<CefString>& accept_filters, int selected_accept_filter, CefRefPtr<CefFileDialogCallback> callback);

	QCefViewBrowserHandler * m_pBrowserHandler;
};


#endif //_QCEFDIALOGHANDLER_H_