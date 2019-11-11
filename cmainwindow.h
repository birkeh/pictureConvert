#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "csplashscreen.h"
#include "common.h"
#include "cexif.h"

#include <QMainWindow>
#include <QCloseEvent>

#include <QStandardItemModel>
#include <QMimeDatabase>

#include <QProgressBar>


QT_BEGIN_NAMESPACE
namespace Ui { class cMainWindow; }
QT_END_NAMESPACE


enum DIRECTORY_METHOD
{
	DIRECTORY_METHOD_KEEP		= 1,
	DIRECTORY_METHOD_NEW		= 2,
	DIRECTORY_METHOD_TAG		= 3,
};

enum FILE_METHOD
{
	FILE_METHOD_KEEP			= 1,
	FILE_METHOD_RENAME			= 2,
};

enum FILE_OVERWRITE
{
	FILE_OVERWRITE_ASK			= 1,
	FILE_OVERWRITE_RENAME		= 2,
	FILE_OVERWRITE_OVERWRITE	= 3,
};

enum FILE_ADD
{
	FILE_ADD_CONVERTED			= 1,
	FILE_ADD_TAG				= 2,
};

typedef struct tagEXPORTSETTINGS
{
	DIRECTORY_METHOD	directoryMethod;
	QString				directory;
	bool				keepStructure;
	QString				directoryTag;
	FILE_METHOD			fileMethod;
	FILE_ADD			fileAdd;
	QString				fileTag;
	FILE_OVERWRITE		fileOverwrite;
	QString				fileFormat;
	int					quality;
} EXPORTSETTINGS;


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
	QProgressBar*					m_lpProgressBar;						/*!< TODO: describe */

	QMimeDatabase					m_mimeDB;
	QList<IMAGEFORMAT>				m_imageFormats;

	bool							m_working;

	void							initUI();
	void							createActions();
	void							createFileActions();
	void							createContextActions();

	void							addPath(const QString& path, bool recursive = true);
	void							addFile(const QString& file);

	bool							isInList(const QString& file);

	void							doExport();
	void							getExportSettings(EXPORTSETTINGS& exportSettings);
	bool							exportFile(const EXPORTSETTINGS& exportSettings, cEXIF* lpExif, bool overwriteAll);
	QString							replaceTags(const QString& path, cEXIF* lpExif, const QString& extension = QString(""), bool directory = true);
	QString							findFreeFileName(const QString& fileName);

	void							setImageFormats();
	void							addImageFormat(const char* shortName, const char* description, const char* extension, QList<QByteArray>& readList, QList<QByteArray>& writeList);

private slots:
	void							onAddFile();
	void							onAddFolder();
	void							onRemoveSelected();
	void							onClearList();
	void							onConvert();

	void							onThumbnailSize(int size);

	void							onAddEntrys(const QStringList& fileList);
	void							onDeleteEntrys();

protected:
	void							closeEvent(QCloseEvent* event);
};
#endif // CMAINWINDOW_H
