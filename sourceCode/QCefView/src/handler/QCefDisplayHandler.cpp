#include "QCefDisplayHandler.h"
#include "QCefViewBrowserHandler.h"

QCefDisplayHandler::QCefDisplayHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefDisplayHandler::~QCefDisplayHandler()
{

}

void QCefDisplayHandler::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) 
{
	CEF_REQUIRE_UI_THREAD();
	QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_,
		"onUrlChange",
		Qt::QueuedConnection,
		Q_ARG(const QString&, QString::fromStdString(url.ToString())));
}

void QCefDisplayHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
}

void QCefDisplayHandler::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__;
	QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_,
		"onFullScreen",
		Qt::QueuedConnection,
		Q_ARG(const bool&, fullscreen));
}

void QCefDisplayHandler::OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__ << QString::fromStdString(value.ToString());
}

bool QCefDisplayHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line)
{
	CEF_REQUIRE_UI_THREAD();

	if (source.empty() || message.empty())
	{
		return false;
	}
	std::string src = source.ToString();
	std::size_t found = src.find_last_of("/\\");
	if (found != std::string::npos && found < src.length() - 1)
	{
		src = src.substr(found + 1);
	}
	qDebug() << __FUNCTION__ << QString::fromStdString(src) << QString::fromStdString(message.ToString());
	return false;
}
