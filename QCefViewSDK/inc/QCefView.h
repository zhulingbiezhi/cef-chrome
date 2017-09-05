#ifndef QCEFVIEW_H
#define QCEFVIEW_H
#pragma once

#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QWidget>
#include <QVariantList>
#pragma endregion qt_headers

#include "QCefQuery.h"
#include "QCefEvent.h"
#include "QCefCommon.h"

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
#define QCEFVIEW_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "QCefView.lib")
#endif

/** Outline of QCefView:
 **
 **		+--------------------------------------------------------------+
 **		| QCefView(QWidget)                                          |
 **		|  						                                       |
 **		|    +----------------------------------------------------+    |
 **		|    | WindowWrapper(QWidget)                             |    |
 **		|    |                                                    |    |
 **		|    |    +-------------------------------------------+   |    |
 **		|    |	  | CefWindow(QWindow)                        |   |    |
 **		|    |	  |					                          |   |    |
 **		|    |	  |					                          |   |    |
 **		|    |	  |					                          |   |    |
 **		|    |	  +-------------------------------------------+   |    |
 **		|    |                                                    |    |
 **		|    +----------------------------------------------------+    |
 **		|                                                              |
 **		+--------------------------------------------------------------+
 **
 **	Remarks:
 **		The WindowWrapper and CefWindow are transparent
 **		to upper layer user.
 **
 **/
class CCefWindow;
class QCefInvoker;

class QCEFVIEW_EXPORT QCefView
	: public QWidget
{
	Q_OBJECT

protected slots:


public:
	QCefView(const QString url, QWidget* parent = 0);
	~QCefView();
	void  Close();
	void  Run();

	/** invokerfunction注册实例，只允许注册一个
	**	QCefInvoker* invoker:	继承于QCefInvoker，传递指针即可
	**/
	QCefInvoker*  getInvoker();
	void registerInvoker(QCefInvoker* invoker);

	/** 
	**	UrlCookie操作，查询cookie，设置cookie
	**/
	void getUrlCookie(const QString& url, QList<TCefCookie>& cookieList);
	void getAllCookie(QList<TCefCookie>& cookieList);
	void setCookie(const QString& url, const QString& key, const QString& value);

	/**
	**	获取句柄ID
	**/
	WId  getCefWinId();

	/**	右键菜单定制，不需要定制则不重载
	**	excContextMenu:		执行item
	**	getMenuInfo：		添加item
	**	command:			item的command
	**	index：				item的顺序号
	**  lblName：			item的显示名称
	**  itemEnable：			item的enable
	**/
	virtual bool excContextMenu(int command);
	virtual bool getMenuInfo(int index, int& command, QString& lblName, bool& itemEnable);		//利用switch case语句

	/**navigate to the content
	 **	content:
	 **		HTML content
	 **	url:
	 **		this url is just use to display
	 **
	 **/
	void navigateToString(const QString& content, const QString& url);

	/**navigate the browser to URL
	 **	url:
	 **		target address
	 **
	 **/
	void navigateToUrl(const QString& url);

	/**can the browser go back to previous page.
	 **
	 **/
	bool browserCanGoBack();

	/**can the browser go forward to the next page
	 **
	 **/
	bool browserCanGoForward();

	/**go back to the previous page
	 **
	 **/
	void browserGoBack();

	/**go forward to the next page
	 **
	 **/
	void browserGoForward();

	/**is browser busy loading content
	 **
	 **/
	bool browserIsLoading();

	/**reload the current page
	 **
	 **/
	void browserReload();

	/**stop current loading
	 **
	 **/
	void browserStopLoad();

	bool triggerEvent(int frameId, const QString& name, const QCefEvent& event);

	bool broadcastEvent(const QString& name, const QCefEvent& event);

	bool responseQCefQuery(int64_t query, bool success, const QString& response, int error);

	void notifyMoveOrResizeStarted();

	bool sendEventNotifyMessage(int frameId, const QString& name, const QCefEvent& event);

protected slots:
	/**called when the browser loading state changed
	**	isLoading:
	**		if isLoading is true, means that the browser
	**		is going to load contents, else means loading
	**		operation is going to be done
	**/
	virtual void onLoadStateChange(bool isLoading);

	/**called when the loading operation is started
	**
	**/
	virtual void onLoadStart();

	/**called when the loading operation is done successfully
	**
	**/
	virtual void onLoadEnd(int httpStatusCode);

	/**called when the loading operation is failed
	**
	**/
	virtual void onLoadError(int errorCode,
		const QString& errorMsg,
		const QString& failedUrl);

	//************************************
	// Method:    processQCefUrlRequest
	// FullName:  QCefView::processQCefUrlRequest
	// Access:    virtual protected private 
	// Returns:   void
	// Qualifier:
	// Parameter: const QString & url
	// 
	// Remarks:
	//		this method is always called in the Qt Main UI Thread 
	//************************************
	virtual void processQCefUrlRequest(const QString& url);

	//************************************
	// Method:    processQCefQueryRequest
	// FullName:  QCefView::processQCefQueryRequest
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	// Parameter: QCefQuery reqeust
	// 
	// Remarks:
	//		this method is always called in the Qt Main UI thread.(event loop)
	//************************************
	virtual void processQCefQueryRequest(const QCefQuery& query);

	//************************************
	// Method:    OnUrlChange
	// FullName:  QCefView::OnUrlChange
	// Access:    virtual protected private 
	// Returns:   void
	// Qualifier:
	// Parameter: int browserId
	// Parameter: int frameId
	// Parameter: const QString url
	//************************************ 
	virtual void  onUrlChange(const QString& url);

	//************************************
	// Method:    onKeyEvent
	// FullName:  QCefView::onKeyEvent
	// Access:    virtual protected private 
	// Returns:   void
	// Qualifier:
	// Parameter: const int& key
	//************************************ 
	virtual void  onKeyEvent(const int& key);

private slots:
	//************************************
	// Method:    onFullScreen
	// FullName:  QCefView::onFullScreen
	// Access:    virtual protected private 
	// Returns:   void
	// Qualifier:
	// Parameter: const bool& ful
	//************************************ 
	void onFullScreen(const bool& full);

private:
	friend class QCefQuery;
	QPointer<CCefWindow> pCefWindow_;
	QPointer<QCefInvoker> pCefInvoker_;
};

#endif // QCEFVIEW_H
