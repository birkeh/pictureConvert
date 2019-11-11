#ifndef CTREEVIEW_H
#define CTREEVIEW_H


#include <QTreeView>
#include <QMetaType>

#include <QMimeDatabase>

#include <QStandardItem>


class cTreeView : public QTreeView
{
	Q_OBJECT

public:
	cTreeView(QWidget* parent = Q_NULLPTR);

protected:
	void				dragEnterEvent(QDragEnterEvent *event) override;
	void				dropEvent(QDropEvent *event) override;
	void				dragMoveEvent(QDragMoveEvent *event) override;
	void				dragLeaveEvent(QDragLeaveEvent *event) override;

	void				keyPressEvent(QKeyEvent *event) override;
private:

signals:
	void				addEntrys(const QStringList& fileList);
	void				deleteEntrys();
};

Q_DECLARE_METATYPE(cTreeView*)


#endif // CTREEVIEW_H
