#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <time.h>
using namespace std;

#include "image.h"

int readImageHeader(char[], int &, int &, int &, bool &);
int readImage(char[], ImageType &);
int writeImage(char[], ImageType &);

int rows, cols, Q, val, maskVal, medianValue;


void median(ImageType &corruptImage, int maskHeight, int maskWidth, ImageType &outputImage)
{
  vector<int> medianVector;
  int halfMaskHeight = maskHeight / 2;
  int halfMaskWidth = maskWidth / 2;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {

      medianVector.clear();
      for (int k = -halfMaskHeight; k < halfMaskHeight; k++)
      {
        for (int l = -halfMaskWidth; l < halfMaskWidth; l++)
        {
          if (i + k < 0 || i + k >= rows || j + l < 0 || j + l >= cols)
          {
            medianVector.push_back(0);
          }
          else
          {
            corruptImage.getPixelVal((i + k), (j + l), val);
            medianVector.push_back(val);
          }
        }
      }
      sort(medianVector.begin(), medianVector.end());
      outputImage.setPixelVal(i, j, medianVector[halfMaskHeight * maskWidth + halfMaskWidth]);
    }
  }
}

void corrupt(ImageType &corruptImage, ImageType &initImage)
{
  int value;
  int randNum;

  srand(time(NULL));
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      randNum = rand() % 256;
      if (randNum < 76)
      {
        value = 255;
      }
      else
      {
        initImage.getPixelVal(i, j, value);
      }
      corruptImage.setPixelVal(i, j, value);
    }
  }
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

  //for the corrupted image
  ImageType corruptImage(rows, cols, Q);

  ImageType outputImage(rows, cols, Q);
  
  corrupt(corruptImage, initImage);
  
  median(corruptImage, 7, 7, outputImage);

  writeImage(argv[2], corruptImage);
  writeImage(argv[3], outputImage);

  return (1);
}
