#ifndef QCEFVIEWBROWSERAPP_H_
#define QCEFVIEWBROWSERAPP_H_
#pragma once

#pragma region stl_headers
#include <set>
#pragma endregion stl_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers


class QCefViewBrowserApp
	: public CefApp
	, public CefBrowserProcessHandler
	, public CefRenderProcessHandler
{
public:
	QCefViewBrowserApp();
	~QCefViewBrowserApp();

	class BrowserDelegate : public virtual CefBase 
	{
	public:
		virtual void OnContextInitialized(CefRefPtr<QCefViewBrowserApp> app) {}

		virtual void OnBeforeChildProcessLaunch(CefRefPtr<QCefViewBrowserApp> app,CefRefPtr<CefCommandLine> command_line) {}

		virtual void OnRenderProcessThreadCreated(CefRefPtr<QCefViewBrowserApp> app,CefRefPtr<CefListValue> extra_info) {}
	};
	typedef std::set<CefRefPtr<BrowserDelegate> > BrowserDelegateSet;

private:
	// Creates all of the BrowserDelegate objects. Implemented in
	// client_app_delegates.
	static void CreateBrowserDelegates(BrowserDelegateSet& delegates);

	// Rigster custom schemes handler factories
	static void RegisterCustomSchemesHandlerFactories();

	// Registers custom schemes. Implemented in client_app_delegates.
	static void RegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar);

	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler();
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler();

	//////////////////////////////////////////////////////////////////////////
	// CefApp methods:
	virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line);

	virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar);

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized();

	virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line);

	virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info);
	
private:
	// Set of supported BrowserDelegates. Only used in the browser process.
	BrowserDelegateSet browser_delegates_;
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefViewBrowserApp);

	virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info);

	virtual void OnWebKitInitialized();

	virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser);

	virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser);

	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
};

#endif	//  QCEFVIEWBROWSERAPP_H_
