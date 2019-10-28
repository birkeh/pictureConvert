#ifndef CEXPORTDIALOG_H
#define CEXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class cExportDialog;
}

class cExportDialog : public QDialog
{
	Q_OBJECT

public:
	explicit cExportDialog(QWidget *parent = nullptr);
	~cExportDialog();

private:
	Ui::cExportDialog *ui;

private slots:
	void							onQualityChanged(int value);
};

#endif // CEXPORTDIALOG_H
