#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // GBRG
  for (auto i = 0; i < height; ++i) {
	  // for even row
	  if (i % 2 == 0) {
		  for (auto j = 0; j < width; ++j) {
			  // for even col ---> G
			  if (j % 2 == 0) {
				  bayer[width * i + j] = (rgb[1 + 3 * (width * i + j)]);
			  }
			  // for odd col ---> B
			  else {
				  bayer[width * i + j] = (rgb[2 + 3 * (width * i + j)]);
			  }
		  }
	  }

	  // for odd row
	  else {
		  for (auto j = 0; j < width; ++j) {
			  // for even col ---> R
			  if (j % 2 == 0) {
				  bayer[width * i + j] = (rgb[0 + 3 * (width * i + j)]);
			  }
			  // for odd col ---> G
			  else {
				  bayer[width * i + j] = (rgb[1 + 3 * (width * i + j)]);
			  }
		  }
	  }
  }

  ////////////////////////////////////////////////////////////////////////////
}
