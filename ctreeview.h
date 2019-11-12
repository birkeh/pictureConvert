/*!
 \file ctreeview.h

*/

#ifndef CTREEVIEW_H
#define CTREEVIEW_H


#include <QTreeView>
#include <QMetaType>

#include <QMimeDatabase>

#include <QStandardItem>


/*!
 \brief

 \class cTreeView ctreeview.h "ctreeview.h"
*/
class cTreeView : public QTreeView
{
	Q_OBJECT

public:
	cTreeView(QWidget* parent = Q_NULLPTR);

protected:
	/*!
	 \brief

	 \fn dragEnterEvent
	 \param event
	*/
	void				dragEnterEvent(QDragEnterEvent *event) override;
	/*!
	 \brief

	 \fn dropEvent
	 \param event
	*/
	void				dropEvent(QDropEvent *event) override;
	/*!
	 \brief

	 \fn dragMoveEvent
	 \param event
	*/
	void				dragMoveEvent(QDragMoveEvent *event) override;
	/*!
	 \brief

	 \fn dragLeaveEvent
	 \param event
	*/
	void				dragLeaveEvent(QDragLeaveEvent *event) override;

	/*!
	 \brief

	 \fn keyPressEvent
	 \param event
	*/
	void				keyPressEvent(QKeyEvent *event) override;
private:

signals:
	/*!
	 \brief

	 \fn addEntrys
	 \param fileList
	*/
	void				addEntrys(const QStringList& fileList);
	/*!
	 \brief

	 \fn deleteEntrys
	*/
	void				deleteEntrys();
};

Q_DECLARE_METATYPE(cTreeView*)


#endif // CTREEVIEW_H
