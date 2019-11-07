#ifndef CFILEDIALOG_H
#define CFILEDIALOG_H


#include <QFileDialog>
#include <QCheckBox>


class cFileDialog : public QFileDialog
{
public:
	cFileDialog(QWidget *parent = nullptr, const QString &caption = QString(), const QString &directory = QString(), const QString &filter = QString());
	cFileDialog(QWidget *parent, Qt::WindowFlags flags);

	void		addCheckbox();
	void		setChecked(bool check);
	bool		checked();

private:
	QCheckBox*	m_lpCheckBox;

	void		init();
};

#endif // CFILEDIALOG_H
