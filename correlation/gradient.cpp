#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

#include "image.h"
#include "gradientMasks.cpp"

int readImageHeader(char[], int &, int &, int &, bool &);
int readImage(char[], ImageType &);
int writeImage(char[], ImageType &);

int rows, cols, Q, val;
double maskVal, testVal;

void shiftValues(vector<double> &gradientVector, double min)
{
  double absValMin = abs(min);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      gradientVector[i * cols + j] += absValMin;
      // cout << gradientVector[i * cols + j] << endl;
    }
  }
}


void setGradientValue(ImageType &initImage, vector<double> gradientVector, ImageType &outputImage)
{
  int max = 0;
  int min = 1000000000;
  int value;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      value = gradientVector[i * cols + j];
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
  shiftValues(gradientVector, min);

  double slope = (255 - 0) / (max - min);

  // max = max / 2;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      double scaledValue = slope *(gradientVector[i * cols + j] - min);
      // cout << (int)scaledValue << endl;
      outputImage.setPixelVal(i, j, (int)gradientVector[i * cols + j]);
    }
  }
}


void getGradient(ImageType &initImage, ImageType &outputImage, bool isX)
{
  vector<double> gradientVector;
  const int maskHeight = 3, maskWidth = 3;
  int halfMaskHeight = maskHeight / 2;
  int halfMaskWidth = maskWidth / 2;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      {
        double sum = 0.0;
        for (int k = -halfMaskHeight; k <= halfMaskHeight; k++)
        {
          for (int l = -halfMaskWidth; l <= halfMaskWidth; l++)
          {
            if (i + k < 0 || i + k >= rows || j + l < 0 || j + l >= cols)
            {
              sum += 0;
            }
            else
            {
              initImage.getPixelVal((i + k), (j + l), val);
              // cout << val;
              if (isX)
              {
                maskVal = prewittX[k + halfMaskHeight][l + halfMaskWidth];
                // cout << maskVal << endl;
              }
              else
              {
                maskVal = prewittY[k + halfMaskHeight][l + halfMaskWidth];
              }
              sum += val * maskVal;
              // cout << sum << endl;
            }
          }
        }
        // cout << sum << endl;
        gradientVector.push_back(sum);
      }
    }
  }
  setGradientValue(initImage, gradientVector, outputImage);
}


void combineGradients(ImageType &xGrad, ImageType &yGrad, ImageType &gradImage) {
  int xVal, yVal, fVal;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      xGrad.getPixelVal(i, j, xVal);
      yGrad.getPixelVal(i,j,yVal);
      fVal = sqrt(pow(xVal, 2) + pow(yVal, 2));
      gradImage.setPixelVal(i,j,fVal);
    }
  }
}


int main(int argc, char *argv[])
{
  // int rows, cols, Q, val;
  bool type;
  int maskRows, maskCols, maskQ;
  bool maskType, isX;

  //for the initial image
  readImageHeader(argv[1], rows, cols, Q, type);
  ImageType initImage(rows, cols, Q);
  readImage(argv[1], initImage);

  ImageType yGrad(rows, cols, Q);
  ImageType xGrad(rows, cols, Q);
  ImageType gradImage(rows, cols, Q);

  getGradient(initImage, xGrad, 1);
  writeImage(argv[2], xGrad);

  getGradient(initImage, yGrad, 0);
  writeImage(argv[3], yGrad);

  combineGradients(xGrad, yGrad, gradImage);
  writeImage(argv[4], gradImage);

  return (1);
}
