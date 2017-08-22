#ifndef CUSTOMCEFVIEW_H
#define CUSTOMCEFVIEW_H

#include <include/QCefView.h>

class CustomCefView 
	: public QCefView
{
	Q_OBJECT

public:
	CustomCefView(const QString& url, QWidget *parent);
	~CustomCefView();

	void changeColor();

protected:
	virtual void processQCefUrlRequest(const QString& url) override;

	virtual void processQCefQueryRequest(const QCefQuery& query) override;

	virtual void onInvokeMethodNotify(const QString method, 
		const QVariantList arguments) override;

	virtual void onLoadStateChange(bool isLoading);

	virtual void onLoadStart();

	virtual void onLoadEnd(int httpStatusCode);

	virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl);

	virtual void dragEnterEvent(QDragEnterEvent *);

	virtual void onUrlChange(const QString& url);

	virtual bool excContextMenu(int id);

	virtual std::list<_contextMenuInfo> getMenuItems();

private:
	
};

#endif // CUSTOMCEFVIEW_H
