#ifndef CEXPORTDIALOG_H
#define CEXPORTDIALOG_H


#include <QDialog>

#include "common.h"


/*
 * altes Verzeichnis
 * neues Verzeichnis, alte Struktur
 * neues Verzeichnis
 *
 * alter Name (umbenennen, wenn gleich)
 * alter Name + _converted
 * alter Name + tag
 * tag
 *
 * überschreiben / fragen / umbenennen
*/

namespace Ui {
class cExportDialog;
}

class cExportDialog : public QDialog
{
	Q_OBJECT

public:
	explicit cExportDialog(const QList<IMAGEFORMAT>& imageFormats, QWidget *parent = nullptr);
	~cExportDialog();

private:
	Ui::cExportDialog *ui;

	void							accept();
	void							reject();

	void							saveSettings();

	void							initUI(const QList<IMAGEFORMAT>& imageFormats);
	void							createActions();

private slots:
	void							onQualityChanged(int value);

	void							onDirectoryMethodChanged(int id);
	void							onFileMethodChanged(int id);
	void							onFileNamePlusChanged(int id);
	void							onFileOverwriteMethodChanged(int id);

protected:
};

#endif // CEXPORTDIALOG_H
