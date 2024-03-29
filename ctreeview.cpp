/*!
 \file ctreeview.cpp

*/

#include "ctreeview.h"

#include <QDropEvent>
#include <QMimeData>
#include <QStandardItemModel>

#include <QDebug>


cTreeView::cTreeView(QWidget* parent) :
	QTreeView(parent)
{
	setAcceptDrops(true);
}

void cTreeView::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasUrls())
	{
		event->acceptProposedAction();
	}
}

void cTreeView::dropEvent(QDropEvent* event)
{
	const QMimeData* mimeData = event->mimeData();

	if(mimeData->hasUrls())
	{
		QStringList	pathList;
		QList<QUrl>	urlList	= mimeData->urls();

		for(int i = 0; i < urlList.size(); i++)
			pathList.append(urlList[i].toLocalFile());

		emit addEntrys(pathList);
	}

	event->acceptProposedAction();
}

void cTreeView::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}

void cTreeView::dragLeaveEvent(QDragLeaveEvent *event)
{
	event->accept();
}

void cTreeView::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Delete)
		emit deleteEntrys();
	else
		QTreeView::keyPressEvent(event);
}
