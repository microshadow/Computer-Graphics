#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <iterator>
using namespace std;

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  std::ofstream out_file;
  //out_file.open(filename, std::ios::out | std::ios::binary);   // write to a file
  out_file.open(filename, std::ios::out);

  if (!out_file.is_open()) {
	  std::cout << "erorr: file cannot open..." << std::endl;
	  return false;
  } 

  else if(out_file.fail())
  {
	  std::cout << "some other errors occur, eg. file extension is not .ppm" << std::endl;
	  out_file.close();
	  return false;
  }

  // in P3 format
  out_file << "P3\n" << width << " " << height << " " << "\n255\n";

  for (int i = 0; i < height; ++i) {
	  for (int j = 0; j < width; ++j) {
		  if (num_channels == 3) {
			  out_file << "    " << (int)(data[num_channels * (width * i + j)])
				  << " " << (int)(data[1 + num_channels * (width * i + j)])
				  << " " << (int)(data[2 + num_channels * (width * i + j)]) << "    ";
		  }
		  else {
			  out_file << "    " << (int)(data[num_channels * (width * i + j)])
				  << " " << (int)(data[num_channels * (width * i + j)])
				  << " " << (int)(data[num_channels * (width * i + j)]) << "    ";
		  }
	  }
	  out_file << "\n";
  }

  //out_file << "   " << (int) r << " " << (int) g << " " << ;

  out_file.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
