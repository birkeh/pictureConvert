/*!
 \file cimage.cpp

*/

#include "cimage.h"

#include <QTransform>
#include <QFileInfo>

#include <QDebug>


cImage::cImage() :
	QImage(),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(const QSize &size, QImage::Format format) :
	QImage(size, format),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(int width, int height, QImage::Format format) :
	QImage(width, height, format),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, format, cleanupFunction, cleanupInfo),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(const uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, format, cleanupFunction, cleanupInfo),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, bytesPerLine, format, cleanupFunction, cleanupInfo),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(const uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction, void *cleanupInfo) :
	QImage(data, width, height, bytesPerLine, format, cleanupFunction, cleanupInfo),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(const QString &fileName, const char *format) :
	QImage(),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
	load(fileName, format);
}

cImage::cImage(const QImage &image) :
	QImage(image),
	m_isChromatic(true),
	m_camType(camera_unknown)
{
}

cImage::cImage(QImage &&other) :
	QImage(other),
	m_isChromatic(true),
	m_camType(camera_unknown)
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


bool cImage::openBuffer(const QString &fileName, const QSharedPointer<QByteArray>& ba, LibRaw& iProcessor)
{
	int			error	= LIBRAW_DATA_ERROR;
	QFileInfo	fi(fileName);

	if(fi.suffix().contains("iiq", Qt::CaseInsensitive) || !ba || ba->isEmpty())
		error	= iProcessor.open_file(fileName.toStdString().c_str());
	else
	{
		if(ba->isEmpty() || ba->size() < 100)
			return(false);

		error	= iProcessor.open_buffer((void*)ba->constData(), static_cast<size_t>(ba->size()));
	}

	return (error == LIBRAW_SUCCESS);
}

void cImage::detectSpecialCamera(const LibRaw & iProcessor)
{
	if(QString(iProcessor.imgdata.idata.model) == "IQ260 Achromatic")
		m_isChromatic = false;

	if (QString(iProcessor.imgdata.idata.model).contains("IQ260"))
		m_camType = camera_iiq;
	else if (QString(iProcessor.imgdata.idata.make).compare("Canon", Qt::CaseInsensitive))
		m_camType = camera_canon;
}

bool cImage::loadRAW(const QString &fileName)
{
	QSharedPointer<QByteArray>	ba;
	LibRaw						iProcessor;

	if(!openBuffer(fileName, ba, iProcessor))
	{
		qDebug() << "could not open buffer";
		return(false);
	}

	detectSpecialCamera(iProcessor);

	int error = iProcessor.unpack();
	if(strcmp(iProcessor.version(), "0.13.5") != 0)	// fixes a bug specific to libraw 13 - version call is UNTESTED
		iProcessor.raw2image();

	if(error != LIBRAW_SUCCESS)
		return(false);

//	cv::Mat	rawMat;

//	LibRaw	RawProcessor;
//	QImage	image;

//	RawProcessor.imgdata.params.gamm[0]			= 1/2.4;
//	RawProcessor.imgdata.params.gamm[1]			= 12.92;
//	RawProcessor.imgdata.params.use_camera_wb	= 1;

//	if(LIBRAW_SUCCESS == RawProcessor.open_file(fileName.toUtf8()))
//	{
//		if(LIBRAW_SUCCESS == RawProcessor.unpack())
//		{
//			if(LIBRAW_SUCCESS == RawProcessor.dcraw_process())
//			{
//				libraw_processed_image_t*	output	= RawProcessor.dcraw_make_mem_image();

//				if(LIBRAW_IMAGE_JPEG == output->type)
//				{
//					image.loadFromData(static_cast<uchar*>(output->data), static_cast<int>(output->data_size), "JPEG");
//					LibRawImagePerformFlip(RawProcessor.imgdata.sizes.flip, image);
//				}
//				else if(LIBRAW_IMAGE_BITMAP == output->type)
//				{
//					image	= LibRawImageToQImage(static_cast<uchar*>(output->data), output->width, output->height, output->colors, output->bits);
//				} // else: could not read
//				LibRaw::dcraw_clear_mem(output);
//			}
//			RawProcessor.recycle();
//		}
//	}
//	*this	= image;

	return(true);
}
