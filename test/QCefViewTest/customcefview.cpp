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

void CustomCefView::onInvokeMethodNotify(
	const QString method, 
	const QVariantList arguments)
{
	if (0 == method.compare("onDragAreaMouseDown"))
	{
		HWND hWnd = ::GetAncestor((HWND)getCefWinId(), GA_ROOT);
		
		// get current mouse cursor position
		POINT pt;
		::GetCursorPos(&pt);

		// in case the mouse is being captured, try to release it
		::ReleaseCapture();

		// simulate that the mouse left button is down on the title area
		::SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, POINTTOPOINTS(pt));
		return;
	}

	QString title("QCef InvokeMethod Notify");
	QString text = QString(
		"Current Thread: QT_UI\r\n"
		"Method: %1\r\n"
		"Arguments: ...")
		.arg(method);

	QMessageBox::information(this->window(), title, text);
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
	//throw std::logic_error("The method or operation is not implemented.");
	return false;
}

std::list<_contextMenuInfo> CustomCefView::getMenuItems()
{
	return std::list<_contextMenuInfo>();
	//throw std::logic_error("The method or operation is not implemented.");
}

//QPaintEngine * CustomCefView::paintEngine() const
//{
//	//qDebug() << __FUNCTION__ ;
//	//throw std::logic_error("The method or operation is not implemented.");
//}
