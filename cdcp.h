#ifndef CDCP_H
#define CDCP_H


#include "dng_camera_profile.h"

#include <QObject>
#include <QMetaObject>
#include <QList>


class cDCP : public QObject
{
	Q_OBJECT
public:
	explicit cDCP(QObject *parent = nullptr);

signals:

public slots:

private:
};

Q_DECLARE_METATYPE(cDCP*)

class cDCPList : public QList<cDCP*>
{
public:
	void		load(const QString& fileName);

private:
	QString		m_fileName;
};

#endif // CDCP_H
