#include "QCefLoadHandler.h"
#include "QCefViewBrowserHandler.h"

QCefLoadHandler::QCefLoadHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefLoadHandler::~QCefLoadHandler()
{

}

void QCefLoadHandler::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	if (m_pBrowserHandler->hostWidget_)
	{
		//m_pBrowserHandler->hostWidget_->onLoadStateChange(isLoading);
		QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_, "onLoadStateChange", Qt::QueuedConnection, Q_ARG(bool, isLoading));
	}
}

void QCefLoadHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	if (m_pBrowserHandler->hostWidget_)
	{
		//m_pBrowserHandler->hostWidget_->onLoadStart();
		QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_, "onLoadStart", Qt::QueuedConnection);
	}
}

void QCefLoadHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	if (m_pBrowserHandler->hostWidget_)
	{
		qDebug() << __FUNCTION__ << QString::fromStdString(frame->GetURL().ToString());
		//m_pBrowserHandler->hostWidget_->onLoadEnd(httpStatusCode);
		QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_, "onLoadEnd", Qt::QueuedConnection, Q_ARG(int, httpStatusCode));
	}
}

void QCefLoadHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	if (errorCode == ERR_ABORTED)
	{
		return;
	}

	QString msg = QString::fromStdString(errorText.ToString());
	QString url = QString::fromStdString(failedUrl.ToString());
	QString content = QString(
		"<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL: %1 </h2>"
		"<h2>Error: %2(%3)</h2>"
		"</body></html>")
		.arg(url)
		.arg(msg).
		arg(errorCode);

	frame->LoadString(content.toLatin1().data(), failedUrl);
	if (m_pBrowserHandler->hostWidget_)
	{
		//m_pBrowserHandler->hostWidget_->onLoadError(errorCode, msg, url);
		QMetaObject::invokeMethod(m_pBrowserHandler->hostWidget_, "onLoadError", Qt::QueuedConnection, Q_ARG(int, errorCode), Q_ARG(const QString&, msg), Q_ARG(const QString&, url));
	}
}
