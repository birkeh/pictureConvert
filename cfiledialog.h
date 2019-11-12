/*!
 \file cfiledialog.h

*/

#ifndef CFILEDIALOG_H
#define CFILEDIALOG_H


#include <QFileDialog>
#include <QCheckBox>


/*!
 \brief

 \class cFileDialog cfiledialog.h "cfiledialog.h"
*/
class cFileDialog : public QFileDialog
{
public:
	cFileDialog(QWidget *parent = nullptr, const QString &caption = QString(), const QString &directory = QString(), const QString &filter = QString());
	/*!
	 \brief

	 \fn cFileDialog
	 \param parent
	 \param flags
	*/
	cFileDialog(QWidget *parent, Qt::WindowFlags flags);

	/*!
	 \brief

	 \fn addCheckbox
	*/
	void		addCheckbox();
	/*!
	 \brief

	 \fn setChecked
	 \param check
	*/
	void		setChecked(bool check);
	/*!
	 \brief

	 \fn checked
	 \return bool
	*/
	bool		checked();

private:
	QCheckBox*	m_lpCheckBox;		/*!< TODO: describe */

	/*!
	 \brief

	 \fn init
	*/
	void		init();
};

#endif // CFILEDIALOG_H
