#pragma once
#include <QWindow>
#include <QPointer>

#include <include/cef_app.h>

#include "inc/QCefView.h"
#include "CefViewBrowserApp/QCefViewBrowserApp.h"
#include "CefViewBrowserApp/QCefViewBrowserHandler.h"
#include "CCookieManager.h"

class CCefWindow :
	public QWindow
{
	Q_OBJECT
#pragma region CEFHWND2QTWIDGET
private:
	typedef std::map<HWND, QPointer<QCefView>> HostWidgetInstanceMap;
	static HostWidgetInstanceMap instance_map_;

public:
	/** Get host Qt widget from native cef browser window handle
	*
	*/
	static QPointer<QCefView> GetHostWidget(HWND h);
#pragma endregion CEFHWND2QTWIDGET

public:
	explicit CCefWindow(const QString& url, QCefView* host, QWindow *parent = 0);
	~CCefWindow();

public:
	/** Get cef view handler associated with current CCefWindow
	 *
	 */
	const CefRefPtr<QCefViewBrowserHandler>& cefViewHandler() const;

	/** set the global cookie
	*
	*/
	void SetCookie(const QString& url, const QString& key, const QString& value);

	/** get the url of global cookie
	*
	*/
	void GetUrlCookie(const QString& url, QList<TCefCookie>& cookieList);

	/** get all of global cookie
	*
	*/
	void GetAllCookie(QList<TCefCookie>& cookieList);

protected:
	void updateCefBrowserWindow();
	virtual void exposeEvent(QExposeEvent *e);
	virtual void resizeEvent(QResizeEvent *e);

public:
	operator HWND();

private:
	HWND								hwndCefBrowser_;
	QPointer<QCefView>					pQCefViewWidget_;
	CefRefPtr<QCefViewBrowserHandler>	pQCefViewHandler;
};

