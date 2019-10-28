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

#include <QImageWriter>


cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen)
{
//	QImageWriter		writer;
//	QList<QByteArray>	list	= writer.supportedImageFormats();

//	writer.setFormat("jpg");
//	QList<QByteArray>	list1	= writer.supportedSubTypes();

//	bool				b;

//	b	= writer.supportsOption(QImageIOHandler::CompressionRatio);
//	b	= writer.supportsOption(QImageIOHandler::Quality);

	initUI();
	createActions();

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

	event->accept();
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

	QIcon::setThemeName("TangoMFK");

	m_lpFileListModel	= new QStandardItemModel;
	ui->m_lpFileList->setModel(m_lpFileListModel);

	QSettings	settings;

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
	items.append(new QStandardItem(QString::number(info.size())));
	items.append(new QStandardItem(info.birthTime().toString("dd.MM.yyyy hh:mm:ss")));
	items.append(new QStandardItem(QString::number(lpExif->imageWidth())));
	items.append(new QStandardItem(QString::number(lpExif->imageHeight())));

	items[3]->setTextAlignment(Qt::AlignRight);
	items[4]->setTextAlignment(Qt::AlignRight);
	items[5]->setTextAlignment(Qt::AlignRight);

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
