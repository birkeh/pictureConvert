/*!
 \file cmainwindow.h

*/

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


/*!
 \brief

 \enum DIRECTORY_METHOD
*/
enum DIRECTORY_METHOD
{
	DIRECTORY_METHOD_KEEP		= 1,
	DIRECTORY_METHOD_NEW		= 2,
	DIRECTORY_METHOD_TAG		= 3,
};

/*!
 \brief

 \enum FILE_METHOD
*/
enum FILE_METHOD
{
	FILE_METHOD_KEEP			= 1,
	FILE_METHOD_RENAME			= 2,
};

/*!
 \brief

 \enum FILE_OVERWRITE
*/
enum FILE_OVERWRITE
{
	FILE_OVERWRITE_ASK			= 1,
	FILE_OVERWRITE_RENAME		= 2,
	FILE_OVERWRITE_OVERWRITE	= 3,
};

/*!
 \brief

 \enum FILE_ADD
*/
enum FILE_ADD
{
	FILE_ADD_CONVERTED			= 1,
	FILE_ADD_TAG				= 2,
};

/*!
 \brief

 \class tagEXPORTSETTINGS cmainwindow.h "cmainwindow.h"
*/
typedef struct tagEXPORTSETTINGS
{
	DIRECTORY_METHOD	directoryMethod;		/*!< TODO: describe */
	QString				directory;				/*!< TODO: describe */
	bool				keepStructure;			/*!< TODO: describe */
	QString				directoryTag;			/*!< TODO: describe */
	FILE_METHOD			fileMethod;				/*!< TODO: describe */
	FILE_ADD			fileAdd;				/*!< TODO: describe */
	QString				fileTag;				/*!< TODO: describe */
	FILE_OVERWRITE		fileOverwrite;			/*!< TODO: describe */
	QString				fileFormat;				/*!< TODO: describe */
	int					quality;				/*!< TODO: describe */
/*!
 \brief

 \typedef EXPORTSETTINGS*/
} EXPORTSETTINGS;

/*!
 \brief

 \enum OVERWRITE
*/
enum OVERWRITE
{
	OVERWRITE_ASK		= 0,
	OVERWRITE_NONE		= 1,
	OVERWRITE_ALL		= 2,
};

/*!
 \brief

 \class cMainWindow cmainwindow.h "cmainwindow.h"
*/
class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cMainWindow
	*/
	~cMainWindow();

private:
	Ui::cMainWindow*				ui;							/*!< TODO: describe */
	cSplashScreen*					m_lpSplashScreen;			/*!< TODO: describe */
	QStandardItemModel*				m_lpFileListModel;			/*!< TODO: describe */
	QProgressBar*					m_lpProgressBar;			/*!< TODO: describe */

	QMimeDatabase					m_mimeDB;					/*!< TODO: describe */
	QList<IMAGEFORMAT>				m_imageFormats;				/*!< TODO: describe */

	bool							m_working;					/*!< TODO: describe */

	QString							m_exportLog;				/*!< TODO: describe */

	/*!
	 \brief

	 \fn initUI
	*/
	void							initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void							createActions();
	/*!
	 \brief

	 \fn createFileActions
	*/
	void							createFileActions();
	/*!
	 \brief

	 \fn createContextActions
	*/
	void							createContextActions();

	/*!
	 \brief

	 \fn addPath
	 \param path
	 \param recursive
	*/
	void							addPath(const QString& path, bool recursive = true);
	/*!
	 \brief

	 \fn addFile
	 \param file
	*/
	void							addFile(const QString& file);

	/*!
	 \brief

	 \fn isInList
	 \param file
	 \return bool
	*/
	bool							isInList(const QString& file);

	/*!
	 \brief

	 \fn doExport
	*/
	void							doExport();
	/*!
	 \brief

	 \fn getExportSettings
	 \param exportSettings
	*/
	void							getExportSettings(EXPORTSETTINGS& exportSettings);
	/*!
	 \brief

	 \fn exportFile
	 \param exportSettings
	 \param lpExif
	 \param overwrite
	 \return OVERWRITE
	*/
	OVERWRITE						exportFile(const EXPORTSETTINGS& exportSettings, cEXIF* lpExif, OVERWRITE overwrite);
	/*!
	 \brief

	 \fn replaceTags
	 \param path
	 \param lpExif
	 \param extension
	 \param directory
	 \return QString
	*/
	QString							replaceTags(const QString& path, cEXIF* lpExif, const QString& extension = QString(""), bool directory = true);
	/*!
	 \brief

	 \fn findFreeFileName
	 \param fileName
	 \return QString
	*/
	QString							findFreeFileName(const QString& fileName);

	/*!
	 \brief

	 \fn setImageFormats
	*/
	void							setImageFormats();
	/*!
	 \brief

	 \fn addImageFormat
	 \param shortName
	 \param description
	 \param extension
	 \param readList
	 \param writeList
	*/
	void							addImageFormat(const char* shortName, const char* description, const char* extension, QList<QByteArray>& readList, QList<QByteArray>& writeList);

	/*!
	 \brief

	 \fn countImages
	*/
	void							countImages();

private slots:
	/*!
	 \brief

	 \fn onAddFile
	*/
	void							onAddFile();
	/*!
	 \brief

	 \fn onAddFolder
	*/
	void							onAddFolder();
	/*!
	 \brief

	 \fn onRemoveSelected
	*/
	void							onRemoveSelected();
	/*!
	 \brief

	 \fn onClearList
	*/
	void							onClearList();
	/*!
	 \brief

	 \fn onConvert
	*/
	void							onConvert();

	/*!
	 \brief

	 \fn onThumbnailSize
	 \param size
	*/
	void							onThumbnailSize(int size);

	/*!
	 \brief

	 \fn onAddEntrys
	 \param fileList
	*/
	void							onAddEntrys(const QStringList& fileList);
	/*!
	 \brief

	 \fn onDeleteEntrys
	*/
	void							onDeleteEntrys();

protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void							closeEvent(QCloseEvent* event);
};
#endif // CMAINWINDOW_H
