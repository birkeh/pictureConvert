#include "cexportdialog.h"
#include "ui_cexportdialog.h"


cExportDialog::cExportDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cExportDialog)
{
	ui->setupUi(this);

	connect(ui->m_lpQualityValue,	&QSlider::valueChanged,	this,	&cExportDialog::onQualityChanged);
}

cExportDialog::~cExportDialog()
{
	delete ui;
}

void cExportDialog::onQualityChanged(int value)
{
	ui->m_lpQualityValue->setNum(value);
}
