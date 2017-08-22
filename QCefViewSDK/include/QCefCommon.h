#ifndef _Q_CEFCOMMON_H_
#define _Q_CEFCOMMON_H_

#include <QDateTime>

struct _contextMenuInfo
{
	int		 index;
	int		 command;
	bool	 enable;
	QString  lableName;
	_contextMenuInfo() :command(-1){

	}
};

struct TCefCookie
{
	int	          secure;			// If |secure| is true the cookie will only be sent for HTTPS requests.
	int		      httponly;			// If |httponly| is true the cookie will only be sent for HTTP requests.
	int			  has_expires;
	QString       cookieName;
	QString       cookieValue;
	QString       host;
	QString       path;
	QDateTime     creation;			// The cookie creation date.
	QDateTime     last_access;		// The cookie last access date.
	QDateTime     expires;			// The cookie expiration date is only valid if |has_expires| is true.
};

#endif //_QCEFCOMMON_H_