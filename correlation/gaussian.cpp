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

const int GAUSS_7[7][7] = {

	{1, 1, 2, 2, 2, 1, 1},
	{1, 2, 2, 4, 2, 2, 1},
	{2, 2, 4, 8, 4, 2, 2},
	{2, 4, 8, 16, 8, 4, 2},
	{2, 2, 4, 8, 4, 2, 2},
	{1, 2, 2, 4, 2, 2, 1},
	{1, 1, 2, 2, 2, 1, 1}
							
};

const int GUASS_15[15][15] = {

	{2, 2,  3,  4,  5,  5,  6,  6,  6,  5,  5,  4,  3, 2, 2},
	{2, 3,  4,  5,  7,  7,  8,  8,  8,  7,  7,  5,  4, 3, 2},
	{3, 4,  6,  7,  9, 10, 10, 11, 10, 10,  9,  7,  6, 4, 3},
	{4, 5,  7,  9, 10, 12, 13, 13, 13, 12, 10,  9,  7, 5, 4},
	{5, 7,  9, 11, 13, 14, 15, 16, 15, 14, 13, 11,  9, 7, 5},
	{5, 7, 10, 12, 14, 16, 17, 18, 17, 16, 14, 12, 10, 7, 5},
	{6, 8, 10, 13, 15, 17, 19, 19, 19, 17, 15, 13, 10, 8, 6},
	{6, 8, 11, 13, 16, 18, 19, 20, 19, 18, 16, 13, 11, 8, 6},
	{6, 8, 10, 13, 15, 17, 19, 19, 19, 17, 15, 13, 10, 8, 6},
	{5, 7, 10, 12, 14, 16, 17, 18, 17, 16, 14, 12, 10, 7, 5},
	{5, 7,  9, 11, 13, 14, 15, 16, 15, 14, 13, 11,  9, 7, 5},
	{4, 5,  7,  9, 10, 12, 13, 13, 13, 12, 10,  9,  7, 5, 4},
	{3, 4,  6,  7,  9, 10, 10, 11, 10, 10,  9,  7,  6, 4, 3},
	{2, 3,  4,  5,  7,  7,  8,  8,  8,  7,  7,  5,  4, 3, 2},
	{2, 2,  3,  4,  5,  5,  6,  6,  6,  5,  5,  4,  3, 2, 2},
};
void writeToArray(ImageType &outputImage, vector<int> smoothedVector) {
    for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      outputImage.setPixelVal(i, j, smoothedVector[i*cols+j]);
    }
  }
}

void normalize(int& max, int&min, double Guass7[][7])
{
  int value;
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      value = GAUSS_7[i][j];
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




  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      double scaledValue = (GAUSS_7[i][j]) / (double)(140);
    //   cout << scaledValue << endl;
      Guass7[i][j] = scaledValue;
    }
  }
}

void smooth(ImageType &initImage,  int maskHeight, int maskWidth, ImageType &outputImage)
{
  int max = 0;
  int min = 1000000000;
  double Guass7[7][7];
  vector<int> smoothedVector;
  int halfMaskHeight = maskHeight / 2;
  int halfMaskWidth = maskWidth / 2;

  normalize(max, min, Guass7);
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
              sum += val * Guass7[k + halfMaskHeight][l + halfMaskWidth];
            //   cout << sum << endl;
            }
          }
        }
        // sum = 140 * sum;
        cout << sum << endl;
        smoothedVector.push_back(sum);
      }
    }
  }
  writeToArray(outputImage, smoothedVector);
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

  smooth(initImage, 7, 7, outputImage);

  writeImage(argv[2], outputImage);

  return (1);
}
