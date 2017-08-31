#include "stdafx.h"

#include <QCoreApplication>
#include <QDir>

#include "CCefSetting.h"

void CCefSetting::initializeInstance()
{
	static CCefSetting s_instance;
}

CefString CCefSetting::browser_sub_process_path;

CefString CCefSetting::resource_directory_path;

CefString CCefSetting::locales_directory_path;

CefString CCefSetting::user_agent;

CCefSetting::CCefSetting()
{
	QDir ExeDir = QCoreApplication::applicationDirPath();
	ExeDir.setPath(ExeDir.canonicalPath());

	QString strExePath = ExeDir.filePath(RENDER_PROCESS_NAME);

	browser_sub_process_path.FromString(QDir::toNativeSeparators(strExePath).toLatin1().data());

	QString strResPath = ExeDir.filePath(RESOURCE_DIRECTORY_NAME);
	resource_directory_path.FromString(QDir::toNativeSeparators(strResPath).toLatin1().data());

	QDir ResPath(strResPath);
	locales_directory_path.FromString(QDir::toNativeSeparators(ResPath.filePath(LOCALES_DIRECTORY_NAME)).toLatin1().data());

	user_agent.FromString(QCEF_USER_AGENT);
}

CCefSetting::~CCefSetting()
{

}
