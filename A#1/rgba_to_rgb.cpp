#include "rgba_to_rgb.h"
#include <iostream>
#include <vector>
void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,  // number of columns
  const int & height, // number of rows
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height * width * 3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int size = width * height;

  // note: do NOT use push_back here, because the vector size has been resized!!!
  for (auto i = 0; i < size; i++) {
	  for (int j = 0; j < 3; j++) {
		  rgb[i * 3 + j] = rgba[i * 4 + j];
	  }
  }

  ////////////////////////////////////////////////////////////////////////////
}
