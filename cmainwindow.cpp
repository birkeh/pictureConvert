#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cimage.h"
#include "cexif.h"
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


cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen)
{
	initUI();
	createActions();

	setImageFormats();
	onClearList();
}

cMainWindow::~cMainWindow()
{
	delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
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
}

void cMainWindow::createActions()
{
	setToolButtonStyle(Qt::ToolButtonFollowStyle);

	createFileActions();
	createContextActions();

	connect(ui->m_lpAddFile,		&QPushButton::clicked,	this,		&cMainWindow::onAddFile);
	connect(ui->m_lpAddFolder,		&QPushButton::clicked,	this,		&cMainWindow::onAddFolder);
	connect(ui->m_lpRemoveSelected,	&QPushButton::clicked,	this,		&cMainWindow::onRemoveSelected);
	connect(ui->m_lpClearList,		&QPushButton::clicked,	this,		&cMainWindow::onClearList);

	connect(ui->m_lpConvert,		&QPushButton::clicked,	this,		&cMainWindow::onConvert);

	connect(ui->m_lpFileList,		&cTreeView::addEntry,	this,		&cMainWindow::onAddEntry);

	connect(ui->m_lpThumbnailSize,	&QSlider::valueChanged,	this,		&cMainWindow::onThumbnailSize);
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

QString cMainWindow::generateReadList()
{
	QString	all("all supported files (");
	QString	readList;

	for(int z = 0;z < m_imageFormats.count();z++)
	{
		IMAGEFORMAT	i	= m_imageFormats[z];

		if(i.read)
		{
			all.append(i.extension);
			all.append(" ");

			readList.append(";;");
			readList.append(i.description);
			readList.append(" (");
			readList.append(i.extension);
			readList.append(")");
		}
	}

	readList.prepend(all);
	return(readList);
}

QString cMainWindow::generateWriteList()
{
	QString	all("all supported files (");
	QString	writeList;

	for(int z = 0;z < m_imageFormats.count();z++)
	{
		IMAGEFORMAT	i	= m_imageFormats[z];

		if(i.write)
		{
			all.append(i.extension);
			all.append(" ");

			writeList.append(";;");
			writeList.append(i.description);
			writeList.append(" (");
			writeList.append(i.extension);
			writeList.append(")");
		}
	}

	writeList.prepend(all);
	return(writeList);
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
	fileDialog.setNameFilter(generateReadList());
	if(!fileDialog.exec())
		return;

	QStringList	fileList	= fileDialog.selectedFiles();

	if(fileList.isEmpty())
		return;

	QFileInfo	info(fileList[0]);

	path	= info.path();
	settings.setValue("import/oldPath", QVariant::fromValue(path));

	for(int i = 0;i < fileList.count();i++)
		onAddEntry(fileList[i]);
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

	addPath(path, checked);

	for(int i = 0;i < m_lpFileListModel->columnCount();i++)
		ui->m_lpFileList->resizeColumnToContents(i);
}

void cMainWindow::onRemoveSelected()
{
}

void cMainWindow::onClearList()
{
	m_lpFileListModel->clear();

	QStringList			headerLabels	= QStringList() << tr("path") << tr("file") << tr("size") << tr("date") << tr("width") << tr("height") << ("");
	m_lpFileListModel->setHorizontalHeaderLabels(headerLabels);
}

void cMainWindow::onAddEntry(const QString& file)
{
	QFileInfo	fileInfo(file);

	if(fileInfo.isDir())
		addPath(file);
	else
	{
		QMimeType	mimeType	= m_mimeDB.mimeTypeForFile(file);

		if(mimeType.name().startsWith("image"))
			addFile(file);
	}

	for(int i = 0;i < m_lpFileListModel->columnCount();i++)
		ui->m_lpFileList->resizeColumnToContents(i);
}

void cMainWindow::addPath(const QString& path, bool recursive)
{
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
	items[0]->setCheckable(true);
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
	cExportDialog*	lpExportDialog	= new cExportDialog(this);
	lpExportDialog->exec();
	delete lpExportDialog;

	for(int i = 0;i < m_lpFileListModel->rowCount();i++)
	{
		QStandardItem*	lpItem	= m_lpFileListModel->item(i, 0);
		if(!lpItem)
			continue;

		cEXIF*			lpExif	= lpItem->data(Qt::UserRole+1).value<cEXIF*>();
		if(!lpExif)
			continue;

		cImage			image(lpExif->fileName());
		if(image.isNull())
			continue;

		QString			newFile	= lpExif->fileName();
		newFile		= newFile.left(newFile.lastIndexOf("."));
		newFile.append("_converted.jpg");

		image.save(newFile);
	}
}

void cMainWindow::onThumbnailSize(int size)
{
	ui->m_lpThumbnailSizeValue->setText(QString::number(size));
	ui->m_lpFileList->setIconSize(QSize(size, size));
}
