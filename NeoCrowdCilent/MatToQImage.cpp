#include "MatToQImage.h"

QImage MatImageToQt(const Mat &src)
{
    if(src.type() == CV_8UC1)
    {
        QImage qImage(src.cols,src.rows,QImage::Format_Indexed8);
        qImage.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            qImage.setColor(i,qRgb(i,i,i));
        }
        uchar *pSrc = src.data;
        for(int row = 0; row < src.rows; row++)
        {
            uchar *pDest = qImage.scanLine(row);
            memcmp(pDest,pSrc,src.cols);
            pSrc += src.step;
        }
        return qImage;
    }
    else if(src.type() == CV_8UC3)
    {
        const uchar *pSrc = (const uchar*)src.data;
        QImage qImage(pSrc,src.cols,src.rows,src.step,QImage::Format_RGB888);
        return qImage.rgbSwapped();
    }
    else if(src.type() == CV_8UC4)
    {
        const uchar *pSrc = (const uchar*)src.data;
        QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
        return qImage.copy();
    }
    else
    {
        return QImage();
    }
}
