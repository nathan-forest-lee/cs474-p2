#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

#include "image.h"

int readImageHeader(char[], int &, int &, int &, bool &);
int readImage(char[], ImageType &);
int writeImage(char[], ImageType &);

int rows, cols, Q, val, maskVal;

void normalize(ImageType &initImage, vector<int> correlatedVector, ImageType &outputImage)
{
  int max = 0;
  int min = 1000000000;
  int value;
  cout << "sit";

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      value = correlatedVector[i * cols + j];
      if (value > max)
      {
        max = value;
      }
      else if (value < min)
      {
        min = value;
      }
    }
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      double scaledValue = 255.0 * ((correlatedVector[i * cols + j] - min) / (double)(max - min));
      outputImage.setPixelVal(i, j, (int)scaledValue);
    }
  }
}

void correlate(ImageType &initImage, ImageType &maskImage, int maskHeight, int maskWidth, ImageType &outputImage)
{
  vector<int> correlationVector;
  maskHeight = maskHeight / 2;
  maskWidth = maskWidth / 2;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      {
        int sum = 0;
        for (int k = -maskHeight; k < maskHeight; k++)
        {
          for (int l = -maskWidth; l < maskWidth; l++)
          {
            if (i + k < 0 || i + k >= rows || j + l < 0 || j + l >= cols)
            {
              sum += 0;
            }
            else
            {
              initImage.getPixelVal((i + k), (j + l), val);
              // cout << val;
              maskImage.getPixelVal((k + maskHeight), (l + maskWidth), maskVal);
              sum += val * maskVal;
              // cout << sum << endl;
            }
          }
        }
        correlationVector.push_back(sum);
      }
    }
  }
  normalize(initImage, correlationVector, outputImage);
}

int main(int argc, char *argv[])
{
  // int rows, cols, Q, val;
  bool type;
  int maskRows, maskCols, maskQ;
  bool maskType;

  //for the initial image
  readImageHeader(argv[1], rows, cols, Q, type);
  ImageType initImage(rows, cols, Q);
  readImage(argv[1], initImage);

  //for the mask image
  readImageHeader(argv[2], maskRows, maskCols, maskQ, maskType);
  ImageType maskImage(maskRows, maskCols, maskQ);
  readImage(argv[2], maskImage);

  ImageType outputImage(rows, cols, Q);

  correlate(initImage, maskImage, maskRows, maskCols, outputImage);

  writeImage(argv[3], outputImage);

  return (1);
}
