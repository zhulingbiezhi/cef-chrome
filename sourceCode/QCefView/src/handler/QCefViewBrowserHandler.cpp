#pragma region stl_headers
#include <sstream>
#include <string>
#pragma endregion stl_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/cef_runnable.h>
#include <include/wrapper/cef_helpers.h>
#pragma endregion cef_headers


#include <QVariant>
#include "QCefViewBrowserHandler.h"
#include "QCefQueryHandler.h"

QCefViewBrowserHandler::QCefViewBrowserHandler(QCefView* host)
	: is_closing_(false)
	, hostWidget_(host)
	, message_router_(NULL)
	, browser_count_(0)
{
	// Create a message Handler
	cefquery_handler_ = new QCefQueryHandler(hostWidget_);
}

QCefViewBrowserHandler::~QCefViewBrowserHandler()
{
}

bool QCefViewBrowserHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
	CEF_REQUIRE_UI_THREAD();
	qDebug() << __FUNCTION__ << QString::fromStdString(message->GetName().ToString());
	if (message_router_->OnProcessMessageReceived(
		browser, source_process, message))
	{
		return true;
	}

	if (DispatchNotifyRequest(browser, source_process, message))
	{
		return true;
	}

	return false;
}

void QCefViewBrowserHandler::setHostWidget(QCefView* host)
{
	hostWidget_ = host;
}

CefRefPtr<CefBrowser> QCefViewBrowserHandler::GetBrowser() const
{
	std::lock_guard<std::mutex> lock_scope(mtx_);
	return main_browser_;
}

int QCefViewBrowserHandler::GetBrowserId() const
{
	std::lock_guard<std::mutex> lock_scope(mtx_);
	return main_browser_id_;
}

void QCefViewBrowserHandler::CloseAllBrowsers(bool force_close)
{
	if (!CefCurrentlyOn(TID_UI))
	{
		// Execute on the UI thread.
		qDebug() << __FUNCTION__ << "warning : close browsers is not on UI_Thread";
		CefPostTask(TID_UI, NewCefRunnableMethod(this, &QCefViewBrowserHandler::CloseAllBrowsers, force_close));
		return;
	}
	qDebug() << __FUNCTION__;
	CloseAllPopupBrowsers(force_close);

	if (main_browser_.get())
	{
		// Request that the main browser close.
		main_browser_->GetHost()->CloseBrowser(force_close);
	}
}

void QCefViewBrowserHandler::CloseAllPopupBrowsers(bool force_close)
{
	if (!CefCurrentlyOn(TID_UI))
	{
		// Execute on the UI thread.
		CefPostTask(TID_UI,
			NewCefRunnableMethod(this, &QCefViewBrowserHandler::CloseAllPopupBrowsers, force_close));
		return;
	}

	if (!popup_browser_list_.empty())
	{
		BrowserList::const_iterator it;
		for (it = popup_browser_list_.begin();
		it != popup_browser_list_.end();
			++it)
		{
			(*it)->GetHost()->CloseBrowser(force_close);
		}
	}
}

bool QCefViewBrowserHandler::IsClosing() const
{
	return is_closing_;
}

bool QCefViewBrowserHandler::TriggerEvent(const CefRefPtr<CefProcessMessage> msg)
{
	if (msg->GetName().empty())
	{
		return false;
	}
	qDebug() << __FUNCTION__ << "send msg to render process----" << QString::fromStdString(msg->GetName().ToString());
	CefRefPtr<CefBrowser> browser = GetBrowser();
	if (browser)
	{
		return browser->SendProcessMessage(PID_RENDERER, msg);
	}

	return false;
}

bool QCefViewBrowserHandler::ResponseQuery(int64_t query, 
	bool success, const CefString& response, int error)
{
	if (cefquery_handler_)
	{
		return cefquery_handler_->Response(query, success, response, error);
	}
	return false;
}

bool QCefViewBrowserHandler::DispatchNotifyRequest(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
	//qDebug() << __FUNCTION__ << source_process << QString::fromStdString(message->GetName().ToString());
	if (hostWidget_ && message->GetName() == INVOKEMETHOD_NOTIFY_MESSAGE)
	{
		CefRefPtr<CefListValue> messageArguments = message->GetArgumentList();
		if (messageArguments && (messageArguments->GetSize() >= 2))
		{
			int idx = 0;
			if (CefValueType::VTYPE_INT == messageArguments->GetType(idx))
			{
				int browserId = browser->GetIdentifier();
				int frameId = messageArguments->GetInt(idx++);

				if (CefValueType::VTYPE_STRING == messageArguments->GetType(idx))
				{
					CefString functionName = messageArguments->GetString(idx++);
					if (functionName == QCEF_INVOKEMETHOD)
					{
						QString method;
						if (CefValueType::VTYPE_STRING == messageArguments->GetType(idx))
						{
							#if defined(CEF_STRING_TYPE_UTF16)
							method = QString::fromWCharArray(messageArguments->GetString(idx++).c_str());
							#elif defined(CEF_STRING_TYPE_UTF8)
							method = QString::fromUtf8(messageArguments->GetString(idx++).c_str());
							#elif defined(CEF_STRING_TYPE_WIDE)
							method = QString::fromWCharArray(messageArguments->GetString(idx++).c_str());
							#endif
						}

						QVariantList arguments;						

						QString qStr;
						for (idx; idx < messageArguments->GetSize(); idx++)
						{
							if (CefValueType::VTYPE_BOOL == messageArguments->GetType(idx))
							{
								arguments.push_back(QVariant::fromValue(
									messageArguments->GetBool(idx)));
							}
							else if (CefValueType::VTYPE_INT == messageArguments->GetType(idx))
							{
								arguments.push_back(QVariant::fromValue(
									messageArguments->GetInt(idx)));
							}
							else if (CefValueType::VTYPE_DOUBLE == messageArguments->GetType(idx))
							{
								arguments.push_back(QVariant::fromValue(
									messageArguments->GetDouble(idx)));
							}
							else if (CefValueType::VTYPE_STRING == messageArguments->GetType(idx))
							{
								#if defined(CEF_STRING_TYPE_UTF16)
								qStr = QString::fromWCharArray(messageArguments->GetString(idx).c_str());
								#elif defined(CEF_STRING_TYPE_UTF8)
								qStr = QString::fromUtf8(messageArguments->GetString(idx).c_str());
								#elif defined(CEF_STRING_TYPE_WIDE)
								qStr = QString::fromWCharArray(messageArguments->GetString(idx).c_str());
								#endif
								arguments.push_back(qStr);
							}
							else if (CefValueType::VTYPE_NULL == messageArguments->GetType(idx))
							{
								arguments.push_back(0);
							}
							else
							{
								// do log
								__noop(_T("QCefView"), _T("Unknow Type!"));
							}
						}
						int maxArgCnt = 5;
						for (int i = arguments.size(); i < maxArgCnt; i++)
						{
							arguments.push_back(QVariant());
						}
						QVariant val1, val2, val3, val4, val5;

						qSwap(val1,arguments[0]);
						qSwap(val2,arguments[1]);
						qSwap(val3,arguments[2]);
						qSwap(val4,arguments[3]);
						qSwap(val5,arguments[4]);
						
						if (hostWidget_.data()->getInvoker() != nullptr)
						{
							QMetaObject::invokeMethod(reinterpret_cast<QObject*>(hostWidget_.data()->getInvoker()),
								method.toLatin1().data(),
								Qt::QueuedConnection,
								QGenericArgument(val1.typeName(), val1.data()),
								QGenericArgument(val2.typeName(), val2.data()),
								QGenericArgument(val3.typeName(), val3.data()),
								QGenericArgument(val4.typeName(), val4.data()),
								QGenericArgument(val5.typeName(), val5.data()));
						}
						else
						{
							qDebug() << __FUNCTION__ << "invoke error : the invoker is empty, please use the function 'registerInvoker' of QCefview first";
						}
						return true;
						}
					}
				}
		}
	}
	return false;
}
