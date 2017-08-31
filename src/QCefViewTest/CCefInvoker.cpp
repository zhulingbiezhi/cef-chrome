#include "CCefInvoker.h"
#include <QDebug>

CCefInvoker::CCefInvoker()
{

}

CCefInvoker::~CCefInvoker()
{

}

void CCefInvoker::TestMethod(int val1, bool val2, QString val3)
{
	qDebug() << __FUNCTION__ << val1 << val2 << val3;
}
