#include "QCefKeyboardHandler.h"
#include "QCefViewBrowserHandler.h"

QCefKeyboardHandler::QCefKeyboardHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefKeyboardHandler::~QCefKeyboardHandler()
{

}

bool QCefKeyboardHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event, bool* is_keyboard_shortcut)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	if (event.windows_key_code == VK_RETURN)
	{
		return true;   //ignore the key code
	}
	else
	{
		if (event.windows_key_code == VK_ESCAPE)			//the key will deal with onKeyEvent
		{
			*is_keyboard_shortcut = true;
		}
		return false;
	}
}

bool QCefKeyboardHandler::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event)
{
	CEF_REQUIRE_UI_THREAD();
	int key = event.windows_key_code;
	qDebug() << __FUNCTION__ << key;
	if (event.type == KEYEVENT_RAWKEYDOWN)
	{
		if (event.windows_key_code == VK_ESCAPE)
		{
			CefRefPtr<CefFrame> frame = browser->GetMainFrame();
			frame->ExecuteJavaScript("{document.webkitExitFullscreen()}", frame->GetURL(), 0);
			return true;
		}
		QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_,
			"onKeyEvent",
			Qt::QueuedConnection,
			Q_ARG(const int&, key)
			);
	}

	return true;
}
