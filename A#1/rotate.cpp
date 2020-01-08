#include "rotate.h"
#include "reflect.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // step 1. we invoke reflect function:
  std::vector<unsigned char> temp;
  temp.resize(width * height * num_channels);
  reflect(input, width, height, 3, temp);

  // step 2. now we have a reflected image, rotate it clockwise. (if we did not invoke reflect, it is counter-clockwise)
  for (auto i = 0; i < height; ++i) {
	  for (auto j = 0; j < width; ++j) {

		  if (j == i) {
			  for (auto k = 0; k < num_channels; ++k) {
				  rotated[k + num_channels * (height * i + j)] = temp[k + num_channels * (width * i + j)];
			  }
		  }
		  else {
			  for (auto k = 0; k < num_channels; ++k) {
				  rotated[k + num_channels * (height * j + i)] = temp[k + num_channels * (width * i + j)];
			  }
		  }
	  }
  }

  ////////////////////////////////////////////////////////////////////////////
}
