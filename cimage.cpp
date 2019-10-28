/*!
 \file cimage.cpp

*/

#include "cimage.h"

#include "libraw/libraw.h"

#include <QTransform>
#include <QFileInfo>


cImage::cImage() :
	QImage()
{

}

cImage::cImage(const QSize &size, QImage::Format format) :
	QImage(size, format)
{
}

cImage::cImage(int width, int height, QImage::Format format) :
	QImage(width, height, format)
{
}

cImage::cImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, format, cleanupFunction, cleanupInfo)
{
}

cImage::cImage(const uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, format, cleanupFunction, cleanupInfo)
{
}

cImage::cImage(uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, bytesPerLine, format, cleanupFunction, cleanupInfo)
{
}

cImage::cImage(const uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, bytesPerLine, format, cleanupFunction, cleanupInfo)
{
}

cImage::cImage(const QString &fileName, const char *format) :
	QImage()
{
	load(fileName, format);
}

cImage::cImage(const QImage &image) :
	QImage(image)
{
}

cImage::cImage(QImage &&other) :
	QImage(other)
{
}

bool cImage::load(const QString &fileName, const char *format)
{
	QFileInfo	fileInfo(fileName);

	if(!fileInfo.suffix().compare("NEF", Qt::CaseInsensitive))
		return(loadRAW(fileName));

	if(QImage::load(fileName, format))
		return(true);

	return(loadRAW(fileName));
}

bool cImage::loadRAW(const QString &fileName)
{
	LibRaw						rawProcessor;
	libraw_processed_image_t*	lpOutput;

	if(rawProcessor.open_file(fileName.toUtf8()) != LIBRAW_SUCCESS)
		return(false);

	if(rawProcessor.unpack() != LIBRAW_SUCCESS)
		return(false);

	rawProcessor.dcraw_process();
	lpOutput	= rawProcessor.dcraw_make_mem_image();

	const	libraw_data_t&	imgdata	= rawProcessor.imgdata;
	uchar*					pixels	= nullptr;

	if(lpOutput->type == LIBRAW_IMAGE_JPEG)
	{
		loadFromData(lpOutput->data, static_cast<int>(lpOutput->data_size), "JPEG");

		if(imgdata.sizes.flip != 0)
		{
			QTransform	rotation;
			int			angle	= 0;

			if(imgdata.sizes.flip == 3)
				angle = 180;
			else if(imgdata.sizes.flip == 5)
				angle = -90;
			else if(imgdata.sizes.flip == 6)
				angle = 90;
			if(angle != 0)
			{
				rotation.rotate(angle);
				*this	= transformed(rotation);
			}
		}
	}
	else
	{
		int	numPixels	= lpOutput->width * lpOutput->height;
		int	colorSize	= lpOutput->bits / 8;
		int	pixelSize	= lpOutput->colors * colorSize;
		pixels			= new uchar[numPixels * 4];
		uchar*	data	= lpOutput->data;

		for(int i = 0; i < numPixels; i++, data += pixelSize)
		{
			if(lpOutput->colors == 3)
			{
				pixels[i * 4]		= data[2 * colorSize];
				pixels[i * 4 + 1]	= data[1 * colorSize];
				pixels[i * 4 + 2]	= data[0];
			}
			else
			{
				pixels[i * 4]		= data[0];
				pixels[i * 4 + 1]	= data[0];
				pixels[i * 4 + 2]	= data[0];
			}
		}
		*this	= QImage(pixels, lpOutput->width, lpOutput->height, QImage::Format_RGB32);
	}

	rawProcessor.recycle();

	return(true);
}
