/*!
 \file cimage.cpp

*/

#include "cimage.h"

#include "libraw/libraw.h"

#include <QTransform>
#include <QFileInfo>

#include <QDebug>


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

#include <math.h>

QImage LibRawImageToQImage(const uchar *data, const int width, const int height, const int nCols, const int colorBits)
{
	int		colorSize	= (colorBits % 8) == 0 ? colorBits / 8 : static_cast<int>(ceil(static_cast<double>(colorBits) / 8.0));
	int		numPixels	= width * height;
	int		pixelSize	=  nCols * colorSize;
	uchar*	pixels		= new uchar[numPixels * 3];

	for(int i = 0; i < numPixels; i++, data += pixelSize)
	{
		if(nCols == 3)
		{
			// this ordering produces correct RGB results - don't ask why
			// tested with .CR2 (Canon)
			pixels[i * 3] = data[3*colorSize];
			pixels[i * 3 + 1] = data[colorSize];
			pixels[i * 3 + 2] = data[2*colorSize];
		}
		else
		{
			pixels[i * 3] = data[0];
			pixels[i * 3 + 1] = data[0];
			pixels[i * 3 + 2] = data[0];
		}
	}
	// immediately create a copy since otherwise we'd have to
	// 'delete[] pixels' somewhere else, ourselves
	// see http://doc.qt.io/qt-5.5/qimage.html#QImage-6
	QImage	out			= QImage(pixels, width, height, width * 3, QImage::Format_RGB888).copy();
//	QImage	out			= QImage(pixels, width, height, width * 3, QImage::Format_RGB32).copy();
	delete[] pixels;
	return out;
}

void LibRawImagePerformFlip(const int flip, QImage& image)
{
	if(flip != 0)
	{
		QTransform	rotation;
		int			angle	= 0;

		if(flip == 3)
			angle = 180;
		else if(flip == 5)
			angle = -90;
		else if(flip == 6)
			angle = 90;

		if (angle != 0)
		{
			rotation.rotate(angle);
			image	= image.transformed(rotation);
		}
	}
}


bool cImage::loadRAW(const QString &fileName)
{
	LibRaw	RawProcessor;
	QImage	image;

//	RawProcessor.imgdata.params.gamm[0]			= 1.00;
//	RawProcessor.imgdata.params.gamm[1]			= 0.00;
//	RawProcessor.imgdata.params.gamm[0]			= 0.45;
//	RawProcessor.imgdata.params.gamm[1]			= 4.50;
	RawProcessor.imgdata.params.gamm[0]			= 1/2.4;
	RawProcessor.imgdata.params.gamm[1]			= 12.92;
//	RawProcessor.imgdata.params.user_qual		= 0; // fastest interpolation (linear)
	RawProcessor.imgdata.params.use_camera_wb	= 1;

	if(LIBRAW_SUCCESS == RawProcessor.open_file(fileName.toUtf8()))
	{
		if(LIBRAW_SUCCESS == RawProcessor.unpack())
		{
			if(LIBRAW_SUCCESS == RawProcessor.dcraw_process())
			{
				libraw_processed_image_t*	output	= RawProcessor.dcraw_make_mem_image();

				if(LIBRAW_IMAGE_JPEG == output->type)
				{
					image.loadFromData(static_cast<uchar*>(output->data), static_cast<int>(output->data_size), "JPEG");
					LibRawImagePerformFlip(RawProcessor.imgdata.sizes.flip, image);
				}
				else if(LIBRAW_IMAGE_BITMAP == output->type)
				{
					image	= LibRawImageToQImage(static_cast<uchar*>(output->data), output->width, output->height, output->colors, output->bits);
				} // else: could not read
				LibRaw::dcraw_clear_mem(output);
			}
			RawProcessor.recycle();
		}
	}
	*this	= image;

	return(true);
}

//bool cImage::loadRAW(const QString &fileName)
//{
//	LibRaw						rawProcessor;
//	libraw_processed_image_t*	lpOutput;

//	rawProcessor.imgdata.params.use_camera_wb		= 1;
//	rawProcessor.imgdata.params.use_auto_wb			= 1;
//	rawProcessor.imgdata.params.use_camera_matrix	= 0;
////	rawProcessor.imgdata.params.gamm[0]				= 1/2.22;
////	rawProcessor.imgdata.params.gamm[1]				= 4.50;
//	rawProcessor.imgdata.params.gamm[0]				= 1/2.40;
//	rawProcessor.imgdata.params.gamm[1]				= 12.92;

//	if(rawProcessor.open_file(fileName.toUtf8()) != LIBRAW_SUCCESS)
//		return(false);

//	if(rawProcessor.unpack() != LIBRAW_SUCCESS)
//		return(false);

//	rawProcessor.raw2image();

//	rawProcessor.dcraw_process();
//	lpOutput	= rawProcessor.dcraw_make_mem_image();

//	const	libraw_data_t&	imgdata	= rawProcessor.imgdata;
//	uchar*					pixels	= nullptr;

//	if(lpOutput->type == LIBRAW_IMAGE_JPEG)
//	{
//		loadFromData(lpOutput->data, static_cast<int>(lpOutput->data_size), "JPEG");

//		if(imgdata.sizes.flip != 0)
//		{
//			QTransform	rotation;
//			int			angle	= 0;

//			if(imgdata.sizes.flip == 3)
//				angle = 180;
//			else if(imgdata.sizes.flip == 5)
//				angle = -90;
//			else if(imgdata.sizes.flip == 6)
//				angle = 90;
//			if(angle != 0)
//			{
//				rotation.rotate(angle);
//				*this	= transformed(rotation);
//			}
//		}
//	}
//	else
//	{
//		int	numPixels	= lpOutput->width * lpOutput->height;
//		int	colorSize	= lpOutput->bits / 8;
//		int	pixelSize	= lpOutput->colors * colorSize;
//		pixels			= new uchar[numPixels * 4];
//		uchar*	data	= lpOutput->data;

//		for(int i = 0; i < numPixels; i++, data += pixelSize)
//		{
//			if(lpOutput->colors == 3)
//			{
//				pixels[i * 4]		= data[2 * colorSize];
//				pixels[i * 4 + 1]	= data[1 * colorSize];
//				pixels[i * 4 + 2]	= data[0];
//			}
//			else
//			{
//				pixels[i * 4]		= data[0];
//				pixels[i * 4 + 1]	= data[0];
//				pixels[i * 4 + 2]	= data[0];
//			}
//		}
//		*this	= QImage(pixels, lpOutput->width, lpOutput->height, QImage::Format_RGB32);
//	}

//	rawProcessor.recycle();

//	return(true);
//}
