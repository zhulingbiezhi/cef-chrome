#include "qcefviewtest.h"

#include <windows.h>
#include "CCefInvoker.h"

#include <QDir>
#include <QCoreApplication>
#include <QHBoxLayout>


QCefViewTest::QCefViewTest(QWidget *parent)
	: QWidget(parent)
{
	CreateUI();
	resize(1366, 900);
	setMinimumSize(1366,768);
	setWindowFlags(Qt::Window);
}

QCefViewTest::~QCefViewTest()
{
	if (mpCefview)
	{
		delete mpCefview;
	}

}

void QCefViewTest::CreateUI()
{
	QDir ExeDir = QCoreApplication::applicationDirPath();
	ExeDir.setPath(ExeDir.canonicalPath());
	QString strUrlPath = ExeDir.filePath("web/QCefViewTestPage.html");

	QWidget* viewContainer = new QWidget(this);
	mpCefview = new CustomCefView(strUrlPath, this);
	CCefInvoker*   pInvoker = new CCefInvoker();
	mpCefview->registerInvoker(pInvoker);


	QHBoxLayout*  viewLyt = new QHBoxLayout;
	viewLyt->setSpacing(0);
	viewLyt->setMargin(0);
	viewLyt->addWidget(mpCefview);
	viewContainer->setLayout(viewLyt);

	mpBackBtn = new QPushButton(tr("back"), this);
	mpBackBtn->setFixedSize(50, 30);

	mpForwardBtn = new QPushButton(tr("forward"), this);
	mpForwardBtn->setFixedSize(50 ,30);

	mpReloadBtn = new QPushButton(tr("reload"), this);
	mpReloadBtn->setFixedSize(50, 30);

	mpGotoBtn = new QPushButton(tr("goto"), this);
	mpGotoBtn->setFixedSize(50, 30);

 	mpUrlEidt = new QLineEdit(this);
	mpUrlEidt->setFixedHeight( 30);
	
	QHBoxLayout*  topLyt = new QHBoxLayout;
	topLyt->setSpacing(10);
	topLyt->setMargin(0);
	topLyt->addSpacing(10);
	topLyt->addWidget(mpBackBtn);
	topLyt->addWidget(mpForwardBtn);
	topLyt->addWidget(mpReloadBtn);
	topLyt->addWidget(mpUrlEidt);
	topLyt->addWidget(mpGotoBtn);
	topLyt->addSpacing(10);

	QVBoxLayout*	mainLyt = new QVBoxLayout;
	mainLyt->setSpacing(5);
	mainLyt->setMargin(0);
	mainLyt->addLayout(topLyt);
	mainLyt->addWidget(viewContainer);
	setLayout(mainLyt);

	connect(mpBackBtn, &QPushButton::clicked, this, &QCefViewTest::onBackBtnClick);
	connect(mpForwardBtn, &QPushButton::clicked, this, &QCefViewTest::onForwardBtnClick);
	connect(mpReloadBtn, &QPushButton::clicked, this, &QCefViewTest::onReloadBtnClick);
	connect(mpGotoBtn, &QPushButton::clicked, this, &QCefViewTest::onGotoBtnClick);
}

void QCefViewTest::onBackBtnClick()
{
	mpCefview->browserGoBack();
}

void QCefViewTest::onForwardBtnClick()
{
	mpCefview->browserGoForward();
}

void QCefViewTest::onReloadBtnClick()
{
	mpCefview->browserReload();
}

void QCefViewTest::onGotoBtnClick()
{
 	QString url = mpUrlEidt->text();
 	mpCefview->navigateToUrl(url);
}
