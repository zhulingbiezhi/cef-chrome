#pragma region qt_headers
#include <QCoreApplication>
#include <QResizeEvent>
#include <QPaintDevice>
#include <QPainter>
#include <QDialog>
#pragma endregion qt_headers

#include "QCefViewBrowserApp.h"
#include "QCefViewBrowserHandler.h"
#include "CCefWindow.h"
#include "CCefSetting.h"

#define CEF_BROWSER_WINDOW_CLASS_NAME_A "CefBrowserWindow"

CCefWindow::HostWidgetInstanceMap CCefWindow::instance_map_;

QPointer<QCefView> CCefWindow::GetHostWidget(HWND h)
{
	auto it = instance_map_.find(h);
	if (it != instance_map_.end())
	{
		return it->second;
	}
	return QPointer<QCefView>();
}

CCefWindow::CCefWindow(const QString& url, QCefView* host, QWindow *parent /*= 0*/)
	: QWindow(parent)
	, pQCefViewWidget_(host)
	, hwndCefBrowser_(NULL)
	, pQCefViewHandler_(NULL)
{
	setFlags(Qt::FramelessWindowHint);
	create();	
	pQCefViewHandler_ = new QCefViewBrowserHandler(host);	
	instance_map_[(HWND)winId()] = pQCefViewWidget_;

	InitializeCef();
	CreateBrowser(url);
}

void CCefWindow::InitializeCef()
{
	CCefSetting::initializeInstance();

	CefString(&cef_settings_.browser_subprocess_path) = CCefSetting::browser_sub_process_path;
	CefString(&cef_settings_.resources_dir_path) = CCefSetting::resource_directory_path;
	CefString(&cef_settings_.locales_dir_path) = CCefSetting::locales_directory_path;
	CefString(&cef_settings_.user_agent) = CCefSetting::user_agent;

	//cef_settings_.single_process = true;

	cef_settings_.multi_threaded_message_loop = TRUE;
	cef_settings_.log_severity = LOGSEVERITY_DEFAULT;
	cef_settings_.remote_debugging_port = 7777;

	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	CefMainArgs main_args(hInstance);

	pQCefViewApp_ = new QCefViewBrowserApp();
	// Initialize CEF.
	void* sandboxInfo = NULL;
	if (CefInitialize(main_args, cef_settings_, pQCefViewApp_, sandboxInfo))
	{
		qDebug() << __FUNCTION__ << "info : CefInitialize successfully !";
	}
}

void CCefWindow::CreateBrowser(const QString& url)
{
	// Set window info
	CefWindowInfo window_info;
	RECT rc = { 0 };
	window_info.SetAsChild((HWND)winId(), rc);

	CefBrowserSettings browserSettings;
	browserSettings.plugins = STATE_DISABLED;	// disable all plugins

	// Create the main browser window.
	if (!CefBrowserHost::CreateBrowser(
		window_info,			// window info
		pQCefViewHandler_,			// handler
		url.toLatin1().data(),		// url
		browserSettings,		// settings
		NULL))
	{
		qDebug() << __FUNCTION__ << "error : CreateBrowser failed !";
	}
	else
	{
		qDebug() << __FUNCTION__ << "info : CreateBrowser successfully !";
	}
}

CCefWindow::~CCefWindow()
{
	pQCefViewWidget_ = NULL;

	auto it = instance_map_.find((HWND)winId());
	if (it != instance_map_.end())
	{
		instance_map_.erase(it);
	}

	destroy();
	
	if (hwndCefBrowser_)
	{
		hwndCefBrowser_ = NULL;
	}

	if (pQCefViewHandler_)
	{
		pQCefViewHandler_ = NULL;
	}

	CefShutdown();
}

void CCefWindow::updateCefBrowserWindow()
{
	if (!hwndCefBrowser_)
	{
		hwndCefBrowser_ = ::FindWindowExA((HWND)winId(),
			NULL, CEF_BROWSER_WINDOW_CLASS_NAME_A, NULL);
	}

	if (hwndCefBrowser_)
	{
		::MoveWindow(hwndCefBrowser_, 0, 0,
			width(), height(), TRUE);
	}
}

void CCefWindow::exposeEvent(QExposeEvent *e)
{
	updateCefBrowserWindow();
	return __super::exposeEvent(e);
}

void CCefWindow::resizeEvent(QResizeEvent *e)
{
	updateCefBrowserWindow();
	return __super::resizeEvent(e);
}

CCefWindow::operator HWND()
{
	return (HWND)winId();
}

const CefRefPtr<QCefViewBrowserHandler>& CCefWindow::cefViewHandler() const
{
	return pQCefViewHandler_;
}

const CefRefPtr<QCefViewBrowserApp>& CCefWindow::cefViewApp() const
{
	return pQCefViewApp_;
}

void CCefWindow::SetCookie(const QString& url, const QString& key, const QString& value)
{
	CCefCookie::getInstance().setCookie(url, key, value);
}

void CCefWindow::GetUrlCookie(const QString& url, QList<TCefCookie>& cookieList)
{
	CCefCookie::getInstance().getUrlCookie(url, cookieList);
}

void CCefWindow::GetAllCookie(QList<TCefCookie>& cookieList)
{
	CCefCookie::getInstance().getAllCookie(cookieList);
}

void CCefWindow::Close()
{
	pQCefViewHandler_->CloseAllBrowsers(false);
}

void CCefWindow::Run()
{
	qDebug() << "CEF start message loop";
	CefRunMessageLoop();
	qDebug() << "CEF quit message loop";
}
