#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cimage.h"

#include "cexif.h"

#include "cexportdialog.h"

#include <QSettings>

#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QMimeType>
#include <QList>
#include <QStandardItem>

#include <QImageReader>
#include <QImageWriter>


void cMainWindow::addImageFormat(const char* shortName, const char* extension)
{
	QList<QByteArray>	readList	= QImageReader::supportedImageFormats();
	QList<QByteArray>	writeList	= QImageWriter::supportedImageFormats();

	bool	r	= readList.contains(QByteArray(shortName));
	bool	w	= writeList.contains(QByteArray(shortName));

	if(QString(shortName).isEmpty())
		r	= true;

	IMAGEFORMAT	i;
	i.shortName	= shortName;
	i.extension = extension;
	i.read		= r;
	i.write		= w;
	m_imageFormats.append(i);
}

cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen)
{
	initUI();
	createActions();

	onClearList();

	addImageFormat("bmp", "Windows Bitmap (*.bmp)");
	addImageFormat("gif", "Graphic Interchange Format (optional) (*.gif)");
	addImageFormat("jpg", "Joint Photographic Experts Group (*.jpg)");
	addImageFormat("png", "Portable Network Graphics (*.png)");
	addImageFormat("pbm", "Portable Bitmap (*.pbm)");
	addImageFormat("pgm", "Portable Graymap (*.pgm)");
	addImageFormat("ppm", "Portable Pixmap (*.ppm)");
	addImageFormat("xbm", "X11 Bitmap (*.xbm)");
	addImageFormat("xpm", "X11 Pixmap (*.xpm)");
	addImageFormat("svg", "Scalable Vector Graphics (*.svg)");
	addImageFormat("icns", "Apple Icon Image (*.icns)");
	addImageFormat("jp2", "Joint Photographic Experts Group 2000 (*.jp2)");
	addImageFormat("mng", "Multiple-image Network Graphics (*.mng)");
	addImageFormat("tga", "Truevision Graphics Adapter (*.tga)");
	addImageFormat("tiff", "Tagged Image File Format (*.tiff)");
	addImageFormat("wbmp", "Wireless Bitmap (*.wbmp)");
	addImageFormat("webp", "WebP (*.webp)");
	addImageFormat("", "Hasselblad (*.3fr)");
	addImageFormat("", "Arri_Alexa (*.ari)");
	addImageFormat("", "Sony (*.arw *.srf *.sr2)");
	addImageFormat("", "Casio (*.bay)");
	addImageFormat("", "Blackmagic Design (*.braw)");
	addImageFormat("", "Cintel (*.cri)");
	addImageFormat("", "Canon (*.crw *.cr2 *.cr3)");
	addImageFormat("", "Phase_One (*.cap *.iiq *.eip)");
	addImageFormat("", "Kodak (*.dcs *.dcr *.drf *.k25 *.kdc)");
	addImageFormat("", "Adobe (*.dng)");
	addImageFormat("", "Epson (*.erf)");
	addImageFormat("", "Imacon/Hasselblad raw (*.fff)");
	addImageFormat("", "GoPro (*.gpr)");
	addImageFormat("", "Mamiya (*.mef)");
	addImageFormat("", "Minolta, Agfa (*.mdc)");
	addImageFormat("", "Leaf (*.mos)");
	addImageFormat("", "Minolta, Konica Minolta (*.mrw)");
	addImageFormat("", "Nikon (*.nef *.nrw)");
	addImageFormat("", "Olympus (*.orf)");
	addImageFormat("", "Pentax (*.pef *.ptx)");
	addImageFormat("", "Logitech (*.pxn)");
	addImageFormat("", "RED Digital Cinema (*.R3D)");
	addImageFormat("", "Fuji (*.raf)");
	addImageFormat("", "Panasonic (*.raw *.rw2)");
	addImageFormat("", "Leica (*.raw *.rwl *.dng)");
	addImageFormat("", "Rawzor (*.rwz)");
	addImageFormat("", "Samsung (*.srw)");
	addImageFormat("", "Sigma (*.x3f)");
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

void cMainWindow::onAddFile()
{
}

void cMainWindow::onAddFolder()
{
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

void cMainWindow::addPath(const QString& path)
{
	QDir		dir(path);
	QStringList	dirList		= dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
	QStringList	fileList	= dir.entryList(QDir::Files);

	for(int i = 0;i < dirList.count();i++)
		addPath(path + "/" + dirList[i]);

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
