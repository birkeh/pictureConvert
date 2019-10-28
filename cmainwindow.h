#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "csplashscreen.h"

#include <QMainWindow>
#include <QCloseEvent>

#include <QStandardItemModel>
#include <QMimeDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class cMainWindow; }
QT_END_NAMESPACE

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent = nullptr);
	~cMainWindow();

private:
	Ui::cMainWindow*				ui;
	cSplashScreen*					m_lpSplashScreen;						/*!< TODO: describe */
	QStandardItemModel*				m_lpFileListModel;

	QMimeDatabase					m_mimeDB;


	void							initUI();
	void							createActions();
	void							createFileActions();
	void							createContextActions();

	void							addPath(const QString& path);
	void							addFile(const QString& file);

	bool							isInList(const QString& file);

private slots:
	void							onAddFile();
	void							onAddFolder();
	void							onRemoveSelected();
	void							onClearList();
	void							onConvert();

	void							onAddEntry(const QString& file);

protected:
	void							closeEvent(QCloseEvent* event);
};
#endif // CMAINWINDOW_H
