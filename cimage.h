/*!
 \file cimage.h

*/

#ifndef CIMAGE_H
#define CIMAGE_H


#include "libraw/libraw.h"

#include <QImage>


class cImage : public QImage
{
public:
	cImage();
	cImage(const QSize &size, QImage::Format format);
	cImage(int width, int height, QImage::Format format);
	cImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	cImage(const uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	cImage(uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	cImage(const uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	cImage(const QString &fileName, const char *format = nullptr);
	cImage(const QImage &image);
	cImage(QImage &&other);

	bool	load(const QString &fileName, const char *format = nullptr);

protected:
	enum Cam
	{
		camera_unknown	= 0,
		camera_iiq,
		camera_canon,
		camera_end
	};

private:
	bool	m_isChromatic;
	Cam		m_camType;

	bool	loadRAW(const QString &fileName);

	bool	openBuffer(const QString &fileName, const QSharedPointer<QByteArray>& ba, LibRaw& iProcessor);
	void	detectSpecialCamera(const LibRaw & iProcessor);
};

#endif // CIMAGE_H
