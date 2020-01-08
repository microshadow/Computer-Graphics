#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  for (auto i = 0; i < height; ++i) {

	  for (auto j = 0; j < width; ++j) {
		  int j_temp = width - 1 - j;

		  for (auto k = 0; k < num_channels; ++k) {
			  reflected[k + num_channels * (width * i + j)] = input[k + num_channels * (width * i + j_temp)];
		  }
	  }
  }
  
  // step 2. reflect the 3d matrix
  //std::vector<std::vector<std::vector<unsigned char>>> input_3d_ref;
  //input_3d_ref.resize(height * width * num_channels);

  //std::vector<std::vector<unsigned char>> temp{};
  //for (auto& row : input_3d) {
	 // //std::vector<unsigned char>::iterator col;
	 // for (int i = row.size() - 1; i >= 0; --i) {   // reflecting...
		//  temp.push_back(row[i]);
	 // }
	 // input_3d_ref.push_back(temp);
  //}

  ////////////////////////////////////////////////////////////////////////////
}
