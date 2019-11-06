/*!
 \file cimage.h

*/

#ifndef CIMAGE_H
#define CIMAGE_H


#include "libraw/libraw.h"
#include <opencv2/opencv.hpp>

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

	template <typename num>
	num clip(float val) const
	{
		int vr = qRound(val);

		// trust me I'm an engineer @ -2
		// with -2 we do not get pink in oversaturated areas
		if (vr > std::numeric_limits<num>::max())
			vr = std::numeric_limits<num>::max()-2;
		if (vr < 0)
			vr = 0;

		return static_cast<num>(vr);
	}

	template <typename num>
	num clip(double val) const
	{
		int vr = qRound(val);

		// trust me I'm an engineer @ -2
		// with -2 we do not get pink in oversaturated areas
		if (vr > std::numeric_limits<num>::max())
			vr = std::numeric_limits<num>::max()-2;
		if (vr < 0)
			vr = 0;

		return static_cast<num>(vr);
	}

	template <typename num>
	num clip(int val) const
	{
		int vr = qRound(static_cast<double>(val));

		// trust me I'm an engineer @ -2
		// with -2 we do not get pink in oversaturated areas
		if (vr > std::numeric_limits<num>::max())
			vr = std::numeric_limits<num>::max()-2;
		if (vr < 0)
			vr = 0;

		return static_cast<num>(vr);
	}

private:
	bool	m_isChromatic;
	Cam		m_camType;

	bool	loadRAW(const QString &fileName);

	bool	openBuffer(const QString &fileName, const QSharedPointer<QByteArray>& ba, LibRaw& iProcessor);
	void	detectSpecialCamera(const LibRaw & iProcessor);

	cv::Mat	demosaic(LibRaw & iProcessor);
	cv::Mat	prepareImg(const LibRaw & iProcessor);
	void	whiteBalance(const LibRaw & iProcessor, cv::Mat & img);
	cv::Mat	whiteMultipliers(const LibRaw & iProcessor);
	void	gammaCorrection(const LibRaw & iProcessor, cv::Mat& img);
	cv::Mat	gammaTable(const LibRaw & iProcessor);

	QImage	raw2Img(const LibRaw & iProcessor, cv::Mat & img);
	QImage	mat2QImage(cv::Mat img);
};

#endif // CIMAGE_H
