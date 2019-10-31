#include "cdcp.h"


cDCP::cDCP(QObject* parent) :
	QObject(parent)
{
}

void  cDCPList::load(const QString& fileName)
{
	m_fileName	= fileName;
}
