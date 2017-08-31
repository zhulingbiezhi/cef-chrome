#ifndef CUSTOMCEFVIEW_H
#define CUSTOMCEFVIEW_H

#include <inc/QCefView.h>


enum EContextMenu
{
	ECM_Back,
	ECM_Forward,
	ECM_Reload
};
class CustomCefView : public QCefView
{
	Q_OBJECT

public:
	CustomCefView(const QString& url, QWidget *parent);
	~CustomCefView();

	void changeColor();

protected:
	virtual void processQCefUrlRequest(const QString& url) override;

	virtual void processQCefQueryRequest(const QCefQuery& query) override;

	virtual void onLoadStateChange(bool isLoading) override;

	virtual void onLoadStart() override;

	virtual void onLoadEnd(int httpStatusCode) override;

	virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl) override;

	virtual void dragEnterEvent(QDragEnterEvent *) override;

	virtual void onUrlChange(const QString& url) override;

	virtual bool excContextMenu(int id) override;

	virtual bool getMenuInfo(int index, int& command, QString& lblName, bool& itemEnable) override;

	virtual void onKeyEvent(const int& key);

private:
	
};
#endif // CUSTOMCEFVIEW_H