#include "median.h"

QByteArray createPicture(unsigned char * imageData, int fileSize, int imageWidth, int imageHeight)
{
    QByteArray result;

    BMPheader header;

    header.bfType           = 0x4d42;
    header.bfSize           = fileSize;
    header.bfReserved       = 0;
    header.bfOffBits        = 54;
    header.biSize           = 40;
    header.biWidth          = imageWidth;
    header.biHeight         = imageHeight;
    header.biPlanes         = 1;
    header.biBitCount       = 24;
    header.biCompression    = 0;
    header.biSizeImage      = imageWidth*imageHeight;
    header.biXPelsPerMeter  = 7559;
    header.biYPelsPerMeter  = 7559;
    header.biClrUsed        = 0;
    header.biClrImportant   = 0;

    result.append((char*)&header, sizeof(BMPheader));
    result.append(header.bfOffBits - sizeof(BMPheader), 0);
    result.append((char*)imageData, imageWidth*imageHeight*3);

    return result;
}

void FilterCreation(double ** GKernel, int kernelSize)
{
        // intialising standard deviation to 1.0
        double sigma = 1.0;
        double r, s = 1.0 * sigma * sigma;

        // sum is for normalization
        double sum = 0.0;

        // generating kernel
        for (int x = -kernelSize / 2; x <= kernelSize / 2; x++) {
                for (int y = -kernelSize / 2; y <= kernelSize / 2; y++) {
                        r = sqrt(x * x + y * y);
                        GKernel[x + kernelSize / 2][y + kernelSize / 2] = (exp(-(r * r) / s)) / (M_PI * s);
                        sum += GKernel[x + kernelSize / 2][y + kernelSize / 2];
                }
        }

        // normalising the Kernel р
        for (int i = 0; i < kernelSize / 2; ++i)
                for (int j = 0; j < kernelSize / 2; ++j)
                        GKernel[i][j] /= sum;
}

int getAvg(unsigned char * data, int size, double ** kernel)
{
    double avg = 0;
    int row = -1;

    for (int i = 0; i < size * size; i++)
    {
        if ((i % size) == 0) row++;
        avg += data[i] * kernel[row][i % 5];
    }

    return avg;
}

int getMiddle(unsigned char * data, int size)
{
    std::sort(data, data + size);
    return data[size / 2];
}

unsigned char * getRegion(unsigned char * data, int startX, int startY, int imageWidth, int regionWidth, int regionHeight)
{
    unsigned char * result = new unsigned char[regionWidth * regionHeight];

    for (int k = 0; k < regionHeight; k++)
        for (int i = 0; i < regionWidth; i++)
        {
            result[i + k* regionWidth] = data[(i + startX) + imageWidth * (k+startY)];
        }
    return result;
}

unsigned char * createRegion(int regionSize, unsigned char avg)
{
    unsigned char * result = new unsigned char[regionSize * regionSize];

    for (int i = 0; i < regionSize * regionSize; i++)
        result[i] = avg;

    return result;
}

void filter(unsigned char * image, unsigned char * result,  int width, int height, float bright) {

    double ** GKernel;
    int kernelSize = 5;

    //Выделение памяти для хранения ядра
    GKernel = new double *[kernelSize];
    for (int i = 0; i < kernelSize; i++)
        GKernel[i] = new double[kernelSize];

    //Генерация значений ядра
    FilterCreation(GKernel, kernelSize);

    unsigned char * region = new unsigned char[kernelSize * kernelSize];

    for (int i = 0; i < height-kernelSize; i++)
        for (int k = 0; k < width-kernelSize; k++)
        {
            region = getRegion(image, k, i, width - kernelSize, kernelSize, kernelSize);
            result[k   + i * width] = getMiddle(region, kernelSize*kernelSize);

            region = getRegion(image, k+1, i, width - kernelSize, kernelSize, kernelSize);
            result[k+1 + i * width] = getMiddle(region, kernelSize*kernelSize);

            region = getRegion(image, k+2, i, width - kernelSize, kernelSize, kernelSize);
            result[k+2 + i * width] = getMiddle(region, kernelSize*kernelSize);
        }
}
