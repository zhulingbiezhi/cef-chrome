#include "QCefContextMenuHandler.h"
#include "QCefViewBrowserHandler.h"

QCefContextMenuHandler::QCefContextMenuHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefContextMenuHandler::~QCefContextMenuHandler()
{
	DEBUG_FUNC();
}

void QCefContextMenuHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	int index = 0;
	int command = 0;
	bool enable = true;
	QString lblName;
	bool  ret = false;

	while (true && index < 10)
	{
		ret = m_pBrowserHandler->hostWidget_->getMenuInfo(index, command, lblName, enable);
		if (!ret)
		{
			index++;
			continue;
		}
		if (index == 0)
		{
			model->Clear();
		}
		else
		{
			model->AddSeparator();
		}

		model->AddItem(command, (wchar_t*)lblName.utf16());
		model->SetEnabled(command, enable);
		index++;
	}
}

bool QCefContextMenuHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	int index = 0;
	int command = 0;
	bool enable = true;
	QString lblName;
	if (!m_pBrowserHandler->hostWidget_->getMenuInfo(index, command, lblName, enable))
	{
		return true;
	}
	else
	{
		return m_pBrowserHandler->hostWidget_->excContextMenu(command_id);
	}
}
