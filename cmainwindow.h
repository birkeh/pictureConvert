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


typedef struct tagIMAGEFORMAT
{
	QString	shortName;
	QString	extension;
	bool	read;
	bool	write;
} IMAGEFORMAT;


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
	QList<IMAGEFORMAT>				m_imageFormats;


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

	void							onThumbnailSize(int size);
	void							onAddEntry(const QString& file);

protected:
	void							closeEvent(QCloseEvent* event);
	void							addImageFormat(const char* shortName, const char* extension);
};
#endif // CMAINWINDOW_H
