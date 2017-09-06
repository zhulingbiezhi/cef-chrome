#pragma region stl_headers
#include <string>
#pragma endregion stl_headers

#pragma region cef_headers
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/wrapper/cef_helpers.h>
#pragma endregion cef_headers

#include "QCefViewBrowserHandler.h"
#include "QCefViewBrowserApp.h"
#include "CCefCookie.h"

QCefViewBrowserApp::QCefViewBrowserApp()
{
	
}

QCefViewBrowserApp::~QCefViewBrowserApp()
{
	DEBUG_FUNC();
}
//////////////////////////////////////////////////////////////////////////
void QCefViewBrowserApp::OnBeforeCommandLineProcessing(
	const CefString& process_type, 
	CefRefPtr<CefCommandLine> command_line)
{
	command_line->AppendSwitch("disable-spell-checking");
	command_line->AppendSwitch("disable-extensions");
	command_line->AppendSwitch("disable-pdf-extension");
	command_line->AppendSwitch("enable-direct-write");
	command_line->AppendSwitch("allow-file-access-from-files");
}

void QCefViewBrowserApp::OnRegisterCustomSchemes(
	CefRefPtr<CefSchemeRegistrar> registrar)
{
	RegisterCustomSchemes(registrar);
}


//////////////////////////////////////////////////////////////////////////
void QCefViewBrowserApp::OnContextInitialized()
{
	CEF_REQUIRE_UI_THREAD();
	DEBUG_FUNC();
	// create all browser delegates
	CreateBrowserDelegates(browser_delegates_);

	// Register cookieable schemes with the global cookie manager.

	CefRefPtr<CefCookieManager> manager = CCefCookie::getInstance().getManager();
	DCHECK(manager.get());
	typedef std::vector<CefString> CookiableSchemeSet;
	CookiableSchemeSet cookieable_schemes_;
	cookieable_schemes_.push_back("http");
	cookieable_schemes_.push_back("https");
	manager->SetSupportedSchemes(cookieable_schemes_, NULL);

	RegisterCustomSchemesHandlerFactories();

	BrowserDelegateSet::iterator it = browser_delegates_.begin();
	for (; it != browser_delegates_.end(); ++it)
	{
		(*it)->OnContextInitialized(this);
	}
}

void QCefViewBrowserApp::OnBeforeChildProcessLaunch(
	CefRefPtr<CefCommandLine> command_line)
{
	DEBUG_FUNC();
	BrowserDelegateSet::iterator it = browser_delegates_.begin();
	for (; it != browser_delegates_.end(); ++it)
	{
		(*it)->OnBeforeChildProcessLaunch(this, command_line);
	}
}

void QCefViewBrowserApp::OnRenderProcessThreadCreated(
	CefRefPtr<CefListValue> extra_info)
{
	CEF_REQUIRE_IO_THREAD();
	DEBUG_FUNC();
	BrowserDelegateSet::iterator it = browser_delegates_.begin();
	for (; it != browser_delegates_.end(); ++it)
	{
		(*it)->OnRenderProcessThreadCreated(this, extra_info);
	}
}

void QCefViewBrowserApp::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info)
{
	DEBUG_FUNC();
}

void QCefViewBrowserApp::OnWebKitInitialized()
{
	DEBUG_FUNC();
}

void QCefViewBrowserApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser)
{
	DEBUG_FUNC();
}

void QCefViewBrowserApp::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
	DEBUG_FUNC();
}

void QCefViewBrowserApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	DEBUG_FUNC();
}

void QCefViewBrowserApp::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	DEBUG_FUNC();
}

CefRefPtr<CefRenderProcessHandler> QCefViewBrowserApp::GetRenderProcessHandler()
{
	return this;
}

CefRefPtr<CefBrowserProcessHandler> QCefViewBrowserApp::GetBrowserProcessHandler()
{
	return this;
}