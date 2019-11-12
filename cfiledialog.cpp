/*!
 \file cfiledialog.cpp

*/

#include "cfiledialog.h"

#include <QGridLayout>
#include <QHBoxLayout>


cFileDialog::cFileDialog(QWidget *parent, const QString &caption, const QString &directory, const QString &filter) :
	QFileDialog(parent, caption, directory, filter),
	m_lpCheckBox(nullptr)
{
	init();
}

cFileDialog::cFileDialog(QWidget *parent, Qt::WindowFlags flags) :
	QFileDialog(parent, flags),
	m_lpCheckBox(nullptr)
{
	init();
}

void cFileDialog::init()
{
	setOption(QFileDialog::DontUseNativeDialog);
}

void cFileDialog::addCheckbox()
{
	QGridLayout* mainLayout = dynamic_cast <QGridLayout*>(this->layout());
	if(!mainLayout)
		return;

	QHBoxLayout*	hbl	= new QHBoxLayout(nullptr);
	m_lpCheckBox	= new QCheckBox(QString("search recursive"));
	hbl->addWidget(m_lpCheckBox);
	int num_rows = mainLayout->rowCount();
	mainLayout->addLayout(hbl, num_rows, 0, 1, -1);
}

void cFileDialog::setChecked(bool check)
{
	if(m_lpCheckBox)
		m_lpCheckBox->setChecked(check);
}

bool cFileDialog::checked()
{
	if(m_lpCheckBox)
		return(m_lpCheckBox->checkState() == Qt::Checked);
	else
		return(false);
}
