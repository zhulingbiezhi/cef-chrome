#include "QCefLifeSpanHandler.h"
#include "QCefViewBrowserHandler.h"
#include <include/cef_runnable.h>

QCefLifeSpanHandler::QCefLifeSpanHandler(QCefViewBrowserHandler * pBrowserHandler)
: m_pBrowserHandler(pBrowserHandler)
{

}

QCefLifeSpanHandler::~QCefLifeSpanHandler()
{
	
}

bool QCefLifeSpanHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access)
{
	CEF_REQUIRE_IO_THREAD();
	DEBUG_FUNC();
	// redirect all popup page into the source frame forcefully
	frame->LoadURL(target_url);

	// don't allow new window or tab 
	return true;
}

void QCefLifeSpanHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	if (!m_pBrowserHandler->message_router_)
	{
		// Create the browser-side router for query handling.
		CefMessageRouterConfig config;
		config.js_query_function = QCEF_QUERY_NAME;
		config.js_cancel_function = QCEF_QUERY_CANCEL_NAME;
		m_pBrowserHandler->message_router_ = CefMessageRouterBrowserSide::Create(config);

		// Register handlers with the router.
		m_pBrowserHandler->message_router_->AddHandler(m_pBrowserHandler->cefquery_handler_, false);
	}

	if (!m_pBrowserHandler->GetBrowser())
	{
		std::lock_guard<std::mutex> lock_scope(m_pBrowserHandler->mtx_);
		// We need to keep the main child window, but not popup windows
		m_pBrowserHandler->main_browser_ = browser;
		m_pBrowserHandler->main_browser_id_ = browser->GetIdentifier();

		if (m_pBrowserHandler->hostWidget_)
		{
			QRect rc = m_pBrowserHandler->hostWidget_->rect();
			::MoveWindow(browser->GetHost()->GetWindowHandle(),
				rc.left(), rc.top(), rc.width(), rc.height(), TRUE);
		}
		//qDebug() << __FUNCTION__ << "get browser handler sucess !";
	}
	else if (browser->IsPopup())
	{
		// Add to the list of popup browsers.
		m_pBrowserHandler->popup_browser_list_.push_back(browser);

		// Give focus to the popup browser. Perform asynchronously because the
		// parent window may attempt to keep focus after launching the popup.
		CefPostTask(TID_UI,
			NewCefRunnableMethod(browser->GetHost().get(), &CefBrowserHost::SetFocus, true));
	}
	m_pBrowserHandler->browser_count_++;
}

bool QCefLifeSpanHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	// Closing the main window requires special handling. See the DoClose()
	// documentation in the CEF header for a detailed description of this
	// process.
	if (m_pBrowserHandler->GetBrowserId() == browser->GetIdentifier())
	{
		// Set a flag to indicate that the window close should be allowed.
		m_pBrowserHandler->is_closing_ = true;
	}
	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.
	return false;
}

void QCefLifeSpanHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{	
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	m_pBrowserHandler->message_router_->OnBeforeClose(browser);

	if (m_pBrowserHandler->GetBrowserId() == browser->GetIdentifier())
	{
		// if the main browser is closing, we need to close all the pop up browsers.
		m_pBrowserHandler->CloseAllPopupBrowsers(true);

		{
			std::lock_guard<std::mutex> lock_scope(m_pBrowserHandler->mtx_);
			// Free the browser pointer so that the browser can be destroyed
			m_pBrowserHandler->main_browser_ = NULL;
		}
	}
	else if (browser->IsPopup())
	{
		// Remove from the browser popup list.
		QCefViewBrowserHandler::BrowserList::iterator it;
		for (it = m_pBrowserHandler->popup_browser_list_.begin();
			it != m_pBrowserHandler->popup_browser_list_.end();
			++it)
		{
			if ((*it)->IsSame(browser))
			{
				m_pBrowserHandler->popup_browser_list_.erase(it);
				break;
			}
		}
	}

	if (--m_pBrowserHandler->browser_count_ == 0)
	{
		m_pBrowserHandler->message_router_->RemoveHandler(m_pBrowserHandler->cefquery_handler_);
		delete m_pBrowserHandler->cefquery_handler_;
		m_pBrowserHandler->cefquery_handler_ = NULL;
		m_pBrowserHandler->message_router_ = NULL;
	}
}
