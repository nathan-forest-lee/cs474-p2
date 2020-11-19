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

void setValues(ImageType &initImage, vector<int> averageVector, ImageType &outputImage)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      outputImage.setPixelVal(i, j, averageVector[i*cols + j]);
    }
  }
}

void average(ImageType &initImage,  int maskHeight, int maskWidth, ImageType &outputImage)
{
  vector<int> averageVector;
  int halfMaskHeight = maskHeight / 2;
  int halfMaskWidth = maskWidth / 2;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      {
        int sum = 0;
        for (int k = -halfMaskHeight; k < halfMaskHeight; k++)
        {
          for (int l = -halfMaskWidth; l < halfMaskWidth; l++)
          {
            if (i + k < 0 || i + k >= rows || j + l < 0 || j + l >= cols)
            {
              sum += 0;
            }
            else
            {
              initImage.getPixelVal((i + k), (j + l), val);
              sum += val / (maskHeight * maskWidth);
              
            }
          }
        }
        cout << sum << endl;
        averageVector.push_back(sum);
      }
    }
  }
  setValues(initImage, averageVector, outputImage);
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

  ImageType outputImage(rows, cols, Q);

  average(initImage, 7, 7, outputImage);

  writeImage(argv[2], outputImage);

  return (1);
}
