TEMPLATE = app
TARGET = QCefViewHelper
CONFIG  -= flat
QT += core widgets gui
QMAKE_LFLAGS_RELEASE +=/debug /opt:ref
CONFIG(release, debug|release) {	
	OBJECTS_DIR = temp/release
	DESTDIR = ../../QCefViewSDK/bin/release_x86
	LIBS += ../../dep/cef/lib/Release/libcef.lib
	LIBS += ../../dep/cef/lib/Release/libcef_dll_wrapper.lib 
	QMAKE_CFLAGS_RELEASE += /MT  
	QMAKE_CXXFLAGS_RELEASE += /MT 
}
CONFIG(debug, debug|release) {
	OBJECTS_DIR = temp/debug
	DESTDIR = ../../QCefViewSDK/bin/debug_x86
	LIBS += ../../dep/cef/lib/Debug/libcef.lib 
	LIBS += ../../dep/cef/lib/Debug/libcef_dll_wrapper.lib 
	QMAKE_CFLAGS_DEBUG += /MTd
	QMAKE_CXXFLAGS_DEBUG += /MTd
}

INCLUDEPATH += ../../dep/cef
PRECOMPILED_HEADER = stdafx.h

UI_DIR  = temp/ui
MOC_DIR = temp/moc
RCC_DIR = temp/rcc

HEADERS += ./QCefViewHelper.h \
    ./resource.h \
	./targetver.h \
	../public/QCefCommon.h \
	./CefViewRenderApp/QCefViewRenderApp.h \
	./CefViewRenderApp/RenderDelegates/QCefClient.h \
	./CefViewRenderApp/RenderDelegates/QCefViewDefaultRenderDelegate.h \
	
SOURCES +=  ./stdafx.cpp \
	./QCefViewHelper.cpp \
	./CefViewRenderApp/QCefViewRenderApp.cpp \
	./CefViewRenderApp/RenderDelegates/QCefClient.cpp \
	./CefViewRenderApp/RenderDelegates/QCefViewDefaultRenderDelegate.cpp \
	
	