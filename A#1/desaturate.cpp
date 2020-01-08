#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  int size = rgb.size();

  double h, s, v, r, g, b;
  for (auto i = 0; i < size; i+=3) {
	  rgb_to_hsv((double)rgb[i], (double)rgb[i + 1], (double)rgb[i + 2], h, s, v);
	  s -= factor;
	  if (s < 0) {
		  s = 0;
	  }

	  hsv_to_rgb(h, s, v, r, g, b);
	  desaturated[i] = r;
	  desaturated[i + 1] = g;
	  desaturated[i + 2] = b;
  }

  ////////////////////////////////////////////////////////////////////////////
}
