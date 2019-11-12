/*!
 \file cmainwindow.cpp

*/

#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cimage.h"
#include "cexportdialog.h"
#include "cfiledialog.h"

#include <QSettings>

#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QMimeType>
#include <QList>
#include <QStandardItem>

#include <QFileDialog>

#include <QImageReader>
#include <QImageWriter>

#include <QMessageBox>


cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen),
	m_lpProgressBar(nullptr),
	m_working(false)
{
	initUI();
	createActions();

	setImageFormats();
}

cMainWindow::~cMainWindow()
{
	delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
	if(m_working)
	{
		QMessageBox::information(this, tr("Close"), tr("Can't close, pictureConvert is working."));
		event->ignore();
		return;
	}

	QSettings	settings;
	settings.setValue("main/width", QVariant::fromValue(size().width()));
	settings.setValue("main/height", QVariant::fromValue(size().height()));
	settings.setValue("main/x", QVariant::fromValue(x()));
	settings.setValue("main/y", QVariant::fromValue(y()));
	if(this->isMaximized())
		settings.setValue("main/maximized", QVariant::fromValue(true));
	else
		settings.setValue("main/maximized", QVariant::fromValue(false));

	settings.setValue("main/thumbnailSize", QVariant::fromValue(ui->m_lpThumbnailSize->value()));

	event->accept();
}

void cMainWindow::initUI()
{
	QSettings	settings;

	ui->setupUi(this);

	ui->m_lpThumbnailSize->setValue(settings.value("main/thumbnailSize", QVariant::fromValue(128)).toInt());
	onThumbnailSize(ui->m_lpThumbnailSize->value());

	QIcon::setThemeName("TangoMFK");

	m_lpFileListModel	= new QStandardItemModel;
	ui->m_lpFileList->setModel(m_lpFileListModel);

	if(!settings.value("main/maximized").toBool())
	{
		qint32		iX		= settings.value("main/x", QVariant::fromValue(-1)).toInt();
		qint32		iY		= settings.value("main/y", QVariant::fromValue(-1)).toInt();
		qint32		iWidth	= settings.value("main/width", QVariant::fromValue(-1)).toInt();
		qint32		iHeight	= settings.value("main/height", QVariant::fromValue(-1)).toInt();

		if(iWidth != -1 && iHeight != -1)
			resize(iWidth, iHeight);
		if(iX != -1 && iY != -1)
			move(iX, iY);
	}

	m_lpProgressBar			= new QProgressBar(this);
	m_lpProgressBar->setVisible(false);
	ui->m_lpStatusBar->addPermanentWidget(m_lpProgressBar);

	QStringList			headerLabels	= QStringList() << tr("path") << tr("file") << tr("size") << tr("date") << tr("width") << tr("height") << ("");
	m_lpFileListModel->setHorizontalHeaderLabels(headerLabels);
}

void cMainWindow::createActions()
{
	setToolButtonStyle(Qt::ToolButtonFollowStyle);

	createFileActions();
	createContextActions();

	connect(ui->m_lpAddFile,		&QPushButton::clicked,		this,		&cMainWindow::onAddFile);
	connect(ui->m_lpAddFolder,		&QPushButton::clicked,		this,		&cMainWindow::onAddFolder);
	connect(ui->m_lpRemoveSelected,	&QPushButton::clicked,		this,		&cMainWindow::onRemoveSelected);
	connect(ui->m_lpClearList,		&QPushButton::clicked,		this,		&cMainWindow::onClearList);
	connect(ui->m_lpFileList,		&cTreeView::deleteEntrys,	this,		&cMainWindow::onDeleteEntrys);

	connect(ui->m_lpConvert,		&QPushButton::clicked,		this,		&cMainWindow::onConvert);

	connect(ui->m_lpFileList,		&cTreeView::addEntrys,		this,		&cMainWindow::onAddEntrys);

	connect(ui->m_lpThumbnailSize,	&QSlider::valueChanged,		this,		&cMainWindow::onThumbnailSize);
}

void cMainWindow::createContextActions()
{
}

void cMainWindow::createFileActions()
{
}

void cMainWindow::setImageFormats()
{
	QList<QByteArray>	readList	= QImageReader::supportedImageFormats();
	QList<QByteArray>	writeList	= QImageWriter::supportedImageFormats();

	addImageFormat("bmp", "Windows Bitmap", "*.bmp", readList, writeList);
	addImageFormat("gif", "Graphic Interchange Format (optional)", "*.gif", readList, writeList);
	addImageFormat("jpg", "Joint Photographic Experts Group", "*.jpg", readList, writeList);
	addImageFormat("png", "Portable Network Graphics", "*.png", readList, writeList);
	addImageFormat("pbm", "Portable Bitmap", "*.pbm", readList, writeList);
	addImageFormat("pgm", "Portable Graymap", "*.pgm", readList, writeList);
	addImageFormat("ppm", "Portable Pixmap", "*.ppm", readList, writeList);
	addImageFormat("xbm", "X11 Bitmap", "*.xbm", readList, writeList);
	addImageFormat("xpm", "X11 Pixmap", "*.xpm", readList, writeList);
	addImageFormat("svg", "Scalable Vector Graphics", "*.svg", readList, writeList);
	addImageFormat("icns", "Apple Icon Image", "*.icns", readList, writeList);
	addImageFormat("jp2", "Joint Photographic Experts Group 2000", "*.jp2", readList, writeList);
	addImageFormat("mng", "Multiple-image Network Graphics", "*.mng", readList, writeList);
	addImageFormat("tga", "Truevision Graphics Adapter", "*.tga", readList, writeList);
	addImageFormat("tiff", "Tagged Image File Format", "*.tiff", readList, writeList);
	addImageFormat("wbmp", "Wireless Bitmap", "*.wbmp", readList, writeList);
	addImageFormat("webp", "WebP", "*.webp", readList, writeList);
	addImageFormat("", "Hasselblad", "*.3fr", readList, writeList);
	addImageFormat("", "Arri_Alexa", "*.ari", readList, writeList);
	addImageFormat("", "Sony", "*.arw *.srf *.sr2", readList, writeList);
	addImageFormat("", "Casio", "*.bay", readList, writeList);
	addImageFormat("", "Blackmagic Design", "*.braw", readList, writeList);
	addImageFormat("", "Cintel", "*.cri", readList, writeList);
	addImageFormat("", "Canon", "*.crw *.cr2 *.cr3", readList, writeList);
	addImageFormat("", "Phase_One", "*.cap *.iiq *.eip", readList, writeList);
	addImageFormat("", "Kodak", "*.dcs *.dcr *.drf *.k25 *.kdc", readList, writeList);
	addImageFormat("", "Adobe", "*.dng", readList, writeList);
	addImageFormat("", "Epson", "*.erf", readList, writeList);
	addImageFormat("", "Imacon/Hasselblad raw", "*.fff", readList, writeList);
	addImageFormat("", "GoPro", "*.gpr", readList, writeList);
	addImageFormat("", "Mamiya", "*.mef", readList, writeList);
	addImageFormat("", "Minolta, Agfa", "*.mdc", readList, writeList);
	addImageFormat("", "Leaf", "*.mos", readList, writeList);
	addImageFormat("", "Minolta, Konica Minolta", "*.mrw", readList, writeList);
	addImageFormat("", "Nikon", "*.nef *.nrw", readList, writeList);
	addImageFormat("", "Olympus", "*.orf", readList, writeList);
	addImageFormat("", "Pentax", "*.pef *.ptx", readList, writeList);
	addImageFormat("", "Logitech", "*.pxn", readList, writeList);
	addImageFormat("", "RED Digital Cinema", "*.R3D", readList, writeList);
	addImageFormat("", "Fuji", "*.raf", readList, writeList);
	addImageFormat("", "Panasonic", "*.raw *.rw2", readList, writeList);
	addImageFormat("", "Leica", "*.raw *.rwl *.dng", readList, writeList);
	addImageFormat("", "Rawzor", "*.rwz", readList, writeList);
	addImageFormat("", "Samsung", "*.srw", readList, writeList);
	addImageFormat("", "Sigma", "*.x3f", readList, writeList);
}

void cMainWindow::addImageFormat(const char* shortName, const char* description, const char* extension, QList<QByteArray>& readList, QList<QByteArray>& writeList)
{
	bool	r	= readList.contains(QByteArray(shortName));
	bool	w	= writeList.contains(QByteArray(shortName));

	if(QString(shortName).isEmpty())
		r	= true;

	IMAGEFORMAT	i;
	i.shortName		= shortName;
	i.description	= description;
	i.extension		= extension;
	i.read			= r;
	i.write			= w;
	m_imageFormats.append(i);
}

void cMainWindow::onAddFile()
{
	QSettings	settings;
	QString		path		= settings.value("import/oldPath", QVariant::fromValue(QDir::homePath())).toString();

	cFileDialog	fileDialog(this);

	fileDialog.setWindowTitle("Import from");
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setDirectory(path);
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	fileDialog.setViewMode(QFileDialog::Detail);
	fileDialog.setNameFilter(generateReadList(m_imageFormats));
	if(!fileDialog.exec())
		return;

	QStringList	fileList	= fileDialog.selectedFiles();

	if(fileList.isEmpty())
		return;

	QFileInfo	info(fileList[0]);

	path	= info.path();
	settings.setValue("import/oldPath", QVariant::fromValue(path));

	onAddEntrys(fileList);
}

void cMainWindow::onAddFolder()
{
	QSettings	settings;
	QString		path		= settings.value("import/oldPath", QVariant::fromValue(QDir::homePath())).toString();
	bool		checked		= settings.value("import/recursive", QVariant::fromValue(false)).toBool();

	cFileDialog	fileDialog(this);

	fileDialog.setWindowTitle("Import from");
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setDirectory(path);
	fileDialog.setFileMode(QFileDialog::DirectoryOnly);
	fileDialog.setViewMode(QFileDialog::Detail);
	fileDialog.addCheckbox();
	fileDialog.setChecked(checked);

	if(!fileDialog.exec())
		return;

	path	= fileDialog.selectedFiles()[0];

	if(path.isEmpty())
		return;

	checked	= fileDialog.checked();

	settings.setValue("import/oldPath", QVariant::fromValue(path));
	settings.setValue("import/recursive", QVariant::fromValue(checked));

	m_working	= true;
	ui->m_lpStatusBar->showMessage(tr("importing..."));
	qApp->processEvents();

	addPath(path, checked);

	for(int i = 0;i < m_lpFileListModel->columnCount();i++)
		ui->m_lpFileList->resizeColumnToContents(i);

	ui->m_lpStatusBar->showMessage(tr("done."), 3000);
	m_working	= false;
}

void cMainWindow::onRemoveSelected()
{
	onDeleteEntrys();
}

void cMainWindow::onClearList()
{
	if(!m_lpFileListModel->rowCount())
		return;

	if(QMessageBox::question(this, tr("Delete"), tr("Do you want to clear the list?")) == QMessageBox::No)
		return;

	m_lpFileListModel->clear();

	QStringList			headerLabels	= QStringList() << tr("path") << tr("file") << tr("size") << tr("date") << tr("width") << tr("height") << ("");
	m_lpFileListModel->setHorizontalHeaderLabels(headerLabels);
}

void cMainWindow::onAddEntrys(const QStringList& fileList)
{
	m_working	= true;
	ui->m_lpStatusBar->showMessage(tr("importing..."));
	qApp->processEvents();

	for(int i = 0;i < fileList.count();i++)
	{
		QString	file	= fileList[i];

		QFileInfo	fileInfo(file);

		if(fileInfo.isDir())
			addPath(file);
		else
		{
			QMimeType	mimeType	= m_mimeDB.mimeTypeForFile(file);

			if(mimeType.name().startsWith("image"))
				addFile(file);
		}
	}

	for(int i = 0;i < m_lpFileListModel->columnCount();i++)
		ui->m_lpFileList->resizeColumnToContents(i);

	ui->m_lpStatusBar->showMessage(tr("done."), 3000);
	m_working	= false;
}

void cMainWindow::addPath(const QString& path, bool recursive)
{
	ui->m_lpStatusBar->showMessage(QString(tr("importing %1...")).arg(path));
	qApp->processEvents();

	QDir		dir(path);
	QStringList	dirList		= dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
	QStringList	fileList	= dir.entryList(QDir::Files);

	if(recursive)
	{
		for(int i = 0;i < dirList.count();i++)
			addPath(path + "/" + dirList[i], recursive);
	}

	for(int i = 0;i < fileList.count();i++)
		addFile(path + "/" + fileList[i]);
}

void cMainWindow::addFile(const QString& file)
{
	ui->m_lpStatusBar->showMessage(QString(tr("importing %1...")).arg(file));
	qApp->processEvents();

	if(isInList(file))
		return;

	QFileInfo	info(file);
	cEXIF*		lpExif	= new cEXIF;

	if(!lpExif->fromFile(file))
	{
		delete lpExif;
		return;
	}

	QList<QStandardItem*>	items;

	items.append(new QStandardItem(info.path()));
	items.append(new QStandardItem(info.fileName()));
	items.append(new QStandardItem(QString::number(info.size()/1024)+" kb"));
	items.append(new QStandardItem(lpExif->dateTime().toString("dd.MM.yyyy hh:mm:ss")));
	items.append(new QStandardItem(QString::number(lpExif->imageWidth())));
	items.append(new QStandardItem(QString::number(lpExif->imageHeight())));

	items[0]->setIcon(QIcon(QPixmap::fromImage(lpExif->thumbnail())));
//	items[0]->setCheckable(true);
	items[2]->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
	items[3]->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
	items[4]->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
	items[5]->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);

	items[0]->setData(QVariant::fromValue(lpExif), Qt::UserRole+1);

	m_lpFileListModel->appendRow(items);

	qApp->processEvents();
}

bool cMainWindow::isInList(const QString& file)
{
	for(int i = 0;i < m_lpFileListModel->rowCount();i++)
	{
		QString			file1	= m_lpFileListModel->item(i, 0)->text() + "/" + m_lpFileListModel->item(i, 1)->text();
		if(!file.compare(file1, Qt::CaseInsensitive))
			return(true);
	}

	return(false);
}

void cMainWindow::onConvert()
{
	cExportDialog	exportDialog(m_imageFormats, this);
	if(exportDialog.exec() == QDialog::Rejected)
		return;

	m_working	= true;
	doExport();
	m_working	= false;
}

void cMainWindow::onThumbnailSize(int size)
{
	ui->m_lpThumbnailSizeValue->setText(QString::number(size));
	ui->m_lpFileList->setIconSize(QSize(size, size));
}

void cMainWindow::doExport()
{
	EXPORTSETTINGS	exportSettings;
	OVERWRITE		overwrite	= OVERWRITE_ASK;

	getExportSettings(exportSettings);

	m_lpProgressBar->setRange(0, m_lpFileListModel->rowCount());
	m_lpProgressBar->setValue(0);
	m_lpProgressBar->setVisible(true);

	for(int i = 0;i < m_lpFileListModel->rowCount();i++)
	{
		QStandardItem*	lpItem	= m_lpFileListModel->item(i, 0);
		if(!lpItem)
			continue;

		cEXIF*			lpExif	= lpItem->data(Qt::UserRole+1).value<cEXIF*>();
		if(!lpExif)
			continue;

		overwrite	= exportFile(exportSettings, lpExif, overwrite);

		m_lpProgressBar->setValue(i);
		qApp->processEvents();
	}

	m_lpProgressBar->setVisible(false);
	ui->m_lpStatusBar->showMessage(tr("export done."), 3000);
}

void cMainWindow::getExportSettings(EXPORTSETTINGS& exportSettings)
{
	QSettings	settings;
	QString		tmp;

	tmp		= settings.value("export/directoryMethod", QVariant::fromValue(QString("keepDirectory"))).toString();

	if(tmp == "newDirectoryTag")
		exportSettings.directoryMethod	= DIRECTORY_METHOD_TAG;
	else if(tmp == "newDirectory")
		exportSettings.directoryMethod	= DIRECTORY_METHOD_NEW;
	else
		exportSettings.directoryMethod	= DIRECTORY_METHOD_KEEP;

	exportSettings.directory			= settings.value("export/destinationPath", QVariant::fromValue(QString(""))).toString();
	exportSettings.keepStructure		= settings.value("export/keepStructure", QVariant::fromValue(false)).toBool();
	exportSettings.directoryTag			= settings.value("export/destinationPathTag", QVariant::fromValue(QString(""))).toString();


	tmp		= settings.value("export/fileMethod", QVariant::fromValue(QString("keepFilename"))).toString();

	if(tmp == "newFilename")
		exportSettings.fileMethod		= FILE_METHOD_RENAME;
	else
		exportSettings.fileMethod		= FILE_METHOD_KEEP;


	tmp		= settings.value("export/filenamePlus", QVariant::fromValue(QString("converted"))).toString();

	if(tmp == "TAG")
		exportSettings.fileAdd			= FILE_ADD_TAG;
	else
		exportSettings.fileAdd			= FILE_ADD_CONVERTED;

	exportSettings.fileTag				= settings.value("export/fileTag", QVariant::fromValue(QString(""))).toString();

	tmp		= settings.value("export/overwrite", QVariant::fromValue(QString("ask"))).toString();

	if(tmp == "overwrite")
		exportSettings.fileOverwrite	= FILE_OVERWRITE_OVERWRITE;
	else if(tmp == "rename")
		exportSettings.fileOverwrite	= FILE_OVERWRITE_RENAME;
	else
		exportSettings.fileOverwrite	= FILE_OVERWRITE_ASK;

	exportSettings.fileFormat			= settings.value("export/fileFormat").toString();
	exportSettings.quality				= settings.value("export/quality", QVariant::fromValue(50)).toInt();
}

OVERWRITE cMainWindow::exportFile(const EXPORTSETTINGS& exportSettings, cEXIF* lpExif, OVERWRITE overwrite)
{
	QString		destPath;
	QString		destFile;
	QFileInfo	fileInfo(lpExif->fileName());
	QString		extension	= exportSettings.fileFormat;

	extension	= extension.mid(extension.lastIndexOf(".")+1);
	extension	= extension.left(extension.length()-1);

	switch(exportSettings.directoryMethod)
	{
	case DIRECTORY_METHOD_NEW:
		destPath	= exportSettings.directory;
		if(exportSettings.keepStructure)
			destPath.append("/" + fileInfo.absolutePath().replace(":", ""));
		break;
	case DIRECTORY_METHOD_KEEP:
		destPath	= fileInfo.absolutePath();
		break;
	case DIRECTORY_METHOD_TAG:
		destPath	= replaceTags(exportSettings.directoryTag, lpExif, extension);
		break;
	}

	switch(exportSettings.fileMethod)
	{
	case FILE_METHOD_KEEP:
		destFile	= fileInfo.baseName() + "." + extension;
		break;
	case FILE_METHOD_RENAME:
		switch(exportSettings.fileAdd)
		{
		case FILE_ADD_CONVERTED:
			destFile	= fileInfo.baseName() + "_converted" + "." + extension;
			break;
		case FILE_ADD_TAG:
			destFile	= replaceTags(exportSettings.fileTag, lpExif, extension, false) + "." + extension;
			break;
		}
		break;
	}

	destFile.prepend(destPath + "/");
	QFileInfo	destInfo(destFile);

	if(destInfo.exists() && overwrite != OVERWRITE_ALL)
	{
		switch(exportSettings.fileOverwrite)
		{
		case FILE_OVERWRITE_ASK:
			{
				QMessageBox::StandardButton	ret	= QMessageBox::question(this, tr("File Exists"), QString(tr("File %1 exists. Do you want to overwrite?")).arg(destFile), QMessageBox::Yes | QMessageBox::No | QMessageBox::YesAll | QMessageBox::NoAll);
				if(ret == QMessageBox::YesAll)
					overwrite	= OVERWRITE_ALL;
				else if(ret == QMessageBox::NoAll)
				{
					overwrite	= OVERWRITE_NONE;
					return(overwrite);
				}
				else if(ret == QMessageBox::No)
					return(overwrite);
			}
			break;
		case FILE_OVERWRITE_RENAME:
			destFile	= findFreeFileName(destFile);
			if(destFile.isEmpty())
			{
				QMessageBox::information(this, tr("File Export"), QString("%1 cannot be renamed.").arg(lpExif->fileName()));
				return(overwrite);
			}
			break;
		case FILE_OVERWRITE_OVERWRITE:
			break;
		}
	}
	else if(overwrite == OVERWRITE_NONE)
		return(overwrite);

	ui->m_lpStatusBar->showMessage(QString(tr("loading %1...")).arg(lpExif->fileName()));
	qApp->processEvents();

	cImage			image(lpExif->fileName());
	if(!image.isNull())
	{
		QTransform	rotation;
		int			angle	= 0;

		switch(lpExif->imageOrientation())
		{
		case 8:
			angle	= 270;
			break;
		case 3:
			angle	= 180;
			break;
		case 6:
			angle	=  90;
			break;
		}

		if(angle != 0)
		{
			rotation.rotate(angle);
			image	= image.transformed(rotation);
		}

		QFileInfo	info(destFile);

		if(info.exists())
			qDebug() << "MACHMA NED!!!";
		else
		{
			ui->m_lpStatusBar->showMessage(QString(tr("converting to %1...")).arg(destFile));
			qApp->processEvents();

			QDir		dir;
			QFileInfo	info(destFile);

			if(dir.mkpath(info.absolutePath()))
				image.save(destFile);
		}
	}

	return(overwrite);
}

QString cMainWindow::replaceTags(const QString& path, cEXIF* lpExif, const QString& extension, bool directory)
{
	QString		dest	= path;
	QFileInfo	fileInfo(lpExif->fileName());

	if(directory)
		dest	= dest.replace("%o", fileInfo.absolutePath());
	else
		dest	= dest.replace("%o", fileInfo.fileName());

	dest		= dest.replace("%y", lpExif->dateTime().toString("yyyy"));
	dest		= dest.replace("%m", lpExif->dateTime().toString("MM"));
	dest		= dest.replace("%d", lpExif->dateTime().toString("dd"));
	dest		= dest.replace("%H", lpExif->dateTime().toString("hh"));
	dest		= dest.replace("%M", lpExif->dateTime().toString("mm"));
	dest		= dest.replace("%S", lpExif->dateTime().toString("ss"));
	dest		= dest.replace("%t", extension);

	dest		= dest.replace("\\", "/");

	return(dest);
}

QString cMainWindow::findFreeFileName(const QString& fileName)
{
	QFileInfo	fileInfo(fileName);
	QString		newName;
	int			number	= 1;

	for(;;)
	{
		newName	= fileInfo.absolutePath() + "/" + fileInfo.baseName() + QString::number(number) + "." + fileInfo.suffix();

		if(!QFileInfo::exists(newName))
			return(newName);
	}
}

void cMainWindow::onDeleteEntrys()
{
	if(!ui->m_lpFileList->selectionModel()->selectedIndexes().count())
		return;

	if(QMessageBox::question(this, tr("Delete"), tr("Do you want to delete selected items?")) == QMessageBox::No)
		return;

	while(!ui->m_lpFileList->selectionModel()->selectedIndexes().isEmpty())
	{
		auto idx	= ui->m_lpFileList->selectionModel()->selectedIndexes().first();
		m_lpFileListModel->removeRow(idx.row(), idx.parent());
	}
}
