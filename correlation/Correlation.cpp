#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

#include "image.h"

int readImageHeader(char[], int&, int&, int&, bool&);
int readImage(char[], ImageType&);
int writeImage(char[], ImageType&);

int rows, cols, Q, val;
void correlate(ImageType& initImage, ImageType& maskImage, int maskHeight, int maskWidth) {
  vector<int> correlationVector;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << "poop";
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

  //for the mask image
  readImageHeader(argv[2], maskRows, maskCols, maskQ, maskType);
  ImageType maskImage(maskRows, maskCols, maskQ);
  readImage(argv[2], maskImage);

  correlate(initImage, maskImage, maskRows, maskCols);

    //  int i, j;
  //  int M, N, Q;
  //  bool type;
  //  int val;
  //  int thresh;

  //  // read image header
  //  readImageHeader(argv[1], N, M, Q, type);

  //  // allocate memory for the image array

  //  ImageType image(N, M, Q);

  //  // read image
  //  readImage(argv[1], image);

  //  cout << "Enter threshold: ";
  //  cin >> thresh;

  //  // threshold image

  //  for(i=0; i<N; i++)
  //    for(j=0; j<M; j++) {
  //      image.getPixelVal(i, j, val);
  //      if(val < thresh)
  //        image.setPixelVal(i, j, 255);
  //      else
  //        image.setPixelVal(i, j, 0);
  //     }

  //  // write image
  //  writeImage(argv[2], image);

  return (1);
}
