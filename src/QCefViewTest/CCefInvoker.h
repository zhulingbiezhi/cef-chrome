#ifndef _CCEFINVOKER_H_
#define _CCEFINVOKER_H_

#include <inc/QCefInvoker.h>

class CCefInvoker : public QCefInvoker
{
	Q_OBJECT
public:
	CCefInvoker();
	~CCefInvoker();

	Q_INVOKABLE void TestMethod(int val1, bool val2, QString val3);
protected:

private:

};


#endif //_CCEFINVOKER_H_