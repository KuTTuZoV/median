#ifndef MEDIAN_H
#define MEDIAN_H

#include <QCoreApplication>
#include "median_global.h"
#include <math.h>

typedef unsigned __int16 WORD;

#pragma pack (push, 1)
typedef struct {
    WORD   bfType;         // 0x4d42 | 0x4349 | 0x5450
    int    bfSize;         // размер файла
    int    bfReserved;     // 0
    int    bfOffBits;      // смещение до поля данных,
                           // обычно 54 = 16 + biSize
    int    biSize;         // размер струкуры в байтах:
                           // 40(BITMAPINFOHEADER) или 108(BITMAPV4HEADER)
                           // или 124(BITMAPV5HEADER)
    int    biWidth;        // ширина в точках
    int    biHeight;       // высота в точках
    WORD   biPlanes;       // всегда должно быть 1
    WORD   biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
    int    biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 |
                           // BI_BITFIELDS | BI_JPEG | BI_PNG
                           // реально используется лишь BI_RGB
    int    biSizeImage;    // Количество байт в поле данных
                           // Обычно устанавливается в 0
    int    biXPelsPerMeter;// горизонтальное разрешение, точек на дюйм
    int    biYPelsPerMeter;// вертикальное разрешение, точек на дюйм
    int    biClrUsed;      // Количество используемых цветов
                           // (если есть таблица цветов)
    int    biClrImportant; // Количество существенных цветов.
                           // Можно считать, просто 0
} BMPheader;
#pragma pack ( pop)

extern "C" {
    MEDIAN_EXPORT void filter(unsigned char * image, unsigned char * result,  int width, int height, float bright);
    MEDIAN_EXPORT QByteArray createPicture(unsigned char * imageData, int fileSize, int imageWidth, int imageHeight);
}

#endif // MEDIAN_H
