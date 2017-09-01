#include <windows.h>
#include <QMessageBox>
#include <QColor>
#include <QDebug>
#include "customcefview.h"


CustomCefView::CustomCefView(const QString& url, QWidget *parent)
	: QCefView(url, parent)
{
	//resize(1600, 900);
}

CustomCefView::~CustomCefView()
{

}

void CustomCefView::changeColor()
{
	qsrand(::GetTickCount());
	QColor color(qrand());

	QCefEvent event("colorChangedEvent");
	event.setStringProperty("color", color.name());
	broadcastEvent("colorChange", event);
}

void CustomCefView::processQCefUrlRequest(const QString& url)
{
	QString title("QCef Url Request");
	QString text = QString(
		"Current Thread: QT_UI\r\n"
		"Url: %1").arg(url);

	QMessageBox::information(this->window(), title, text);
}

void CustomCefView::processQCefQueryRequest(const QCefQuery& query)
{
	QString title("QCef Query Request");
	QString text = QString(
		"Current Thread: QT_UI\r\n"
		"Query: %1").arg(query.reqeust());

	QMessageBox::information(this->window(), title, text);

	QString response = query.reqeust().toUpper();
	query.responseSuccess(response);
}

void CustomCefView::onLoadStateChange(bool isLoading)
{
	qDebug() << __FUNCTION__ << isLoading;
	//throw std::logic_error("The method or operation is not implemented.");
}

void CustomCefView::onLoadStart()
{
	qDebug() << __FUNCTION__ ;
	//throw std::logic_error("The method or operation is not implemented.");
}

void CustomCefView::onLoadEnd(int httpStatusCode)
{
	qDebug() << __FUNCTION__ << httpStatusCode;
	//throw std::logic_error("The method or operation is not implemented.");
}

void CustomCefView::onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl)
{
	qDebug() << __FUNCTION__ << errorCode << errorMsg << failedUrl;
	//throw std::logic_error("The method or operation is not implemented.");
}

void CustomCefView::dragEnterEvent(QDragEnterEvent *)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void CustomCefView::onUrlChange(const QString& url)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

bool CustomCefView::excContextMenu(int id)
{
	switch (id)
	{
	case ECM_Back:
		this->browserGoBack();
		break;
	case ECM_Forward:
		this->browserGoForward();
		break;
	case ECM_Reload:
		this->browserReload();
		break;
	default:;
	}
	return true;
}

bool CustomCefView::getMenuInfo(int index, int& command, QString& lblName, bool& itemEnable)
{
	switch (index)
	{
	case 0:
		command = ECM_Back;
		lblName = tr("back");
		itemEnable = this->browserCanGoBack();
		return true;
	case 1:
		command = ECM_Forward;
		lblName = tr("forward");
		itemEnable = this->browserCanGoForward();
		return true;
	case 2:
		command = ECM_Reload;
		lblName = tr("reload");
		itemEnable = true;
		return true;
	default:
		command = -1;
		lblName = "";
		itemEnable = false;
		return false;
	}
}

void CustomCefView::onKeyEvent(const int& key)
{

}
