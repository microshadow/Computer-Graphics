#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // i = 0.2126 r + 0.7152 g + 0.0722 b
  // coefficients
  unsigned char rValue = 0.2126, gValue = 0.7152, bValue = 0.0722;
  int size = width * height * 3;
	 
  // using average...
  for (int i = 0; i < size; i+=3) {
	  unsigned char average = (rgb[i] + rgb[i + 1] + rgb[i + 2]) / 3;
	  gray[i / 3] = average;
  }

  ////////////////////////////////////////////////////////////////////////////
}