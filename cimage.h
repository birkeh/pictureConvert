/*!
 \file cimage.h

*/

#ifndef CIMAGE_H
#define CIMAGE_H


#include <QImage>


/*!
 \brief

 \class cImage cimage.h "cimage.h"
*/
class cImage : public QImage
{
public:
	cImage();
	/*!
	 \brief

	 \fn cImage
	 \param size
	 \param format
	*/
	cImage(const QSize &size, QImage::Format format);
	/*!
	 \brief

	 \fn cImage
	 \param width
	 \param height
	 \param format
	*/
	cImage(int width, int height, QImage::Format format);
	/*!
	 \brief

	 \fn cImage
	 \param data
	 \param width
	 \param height
	 \param format
	 \param cleanupFunction
	 \param cleanupInfo
	*/
	cImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/*!
	 \brief

	 \fn cImage
	 \param data
	 \param width
	 \param height
	 \param format
	 \param cleanupFunction
	 \param cleanupInfo
	*/
	cImage(const uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/*!
	 \brief

	 \fn cImage
	 \param data
	 \param width
	 \param height
	 \param bytesPerLine
	 \param format
	 \param cleanupFunction
	 \param cleanupInfo
	*/
	cImage(uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/*!
	 \brief

	 \fn cImage
	 \param data
	 \param width
	 \param height
	 \param bytesPerLine
	 \param format
	 \param cleanupFunction
	 \param cleanupInfo
	*/
	cImage(const uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/*!
	 \brief

	 \fn cImage
	 \param fileName
	 \param format
	*/
	cImage(const QString &fileName, const char *format = nullptr);
	/*!
	 \brief

	 \fn cImage
	 \param image
	*/
	cImage(const QImage &image);
	/*!
	 \brief

	 \fn cImage
	 \param other
	*/
	cImage(QImage &&other);

	/*!
	 \brief

	 \fn load
	 \param fileName
	 \param format
	 \return bool
	*/
	bool	load(const QString &fileName, const char *format = nullptr);

private:
	/*!
	 \brief

	 \fn loadRAW
	 \param fileName
	 \return bool
	*/
	bool	loadRAW(const QString &fileName);
};

#endif // CIMAGE_H
